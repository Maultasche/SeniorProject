/*RedWindow.cpp*/

#include <DxGuiFramework.h>
#include <time.h>
#include "DxGuiTestApp.h"
#include "BlueWindow.h"
#include "RedWindow.h"

#define  TITLEBAR_HEIGHT      20
#define  LABEL_OFFSET_X       20
#define  LABEL_OFFSET_Y       10
#define  LABEL_HEIGHT         60

RedWindow::RedWindow() : DGWindow(IDW_REDWINDOW, false)
{
   srand((unsigned)time(NULL));
}

RedWindow::RedWindow(int xPos, int yPos, int width, int height) :
   DGWindow(IDW_REDWINDOW, false, xPos, yPos, width, height)
{

}

void FC RedWindow::OnCreate()
{
   DGWindow::OnCreate();

   testLabel = new DGLabel(IDL_TESTLABEL, this, DGArea(10, 0, 180, 60),
      "Click the button to change the background to a random color", true, 
      DGColor(0, 0, 0), DGColor(255, 0, 0),
      DT_CENTER | DT_WORDBREAK);
 
   testButton = new DGButton(IDB_TESTBUTTON, this, DGArea(75, 110, 140, 30),
      BT_PUSHBUTTON | BT_TEXTBUTTON, "Change Background");

   titleBar = new DGTitleBar(IDC_RED_TITLEBAR, this, 
      DGArea(0, 0, 300, TITLEBAR_HEIGHT), "Red Window",
      DGFont("MS Sans Serif", 16));

   resizeCtrl = new DGResize(IDC_RED_RESIZE, this);

   AddChildWindow(testLabel);
   AddChildWindow(testButton);
   AddChildWindow(titleBar);
   AddChildWindow(resizeCtrl);

   AddMessageHandler(GM_BUTTON_CLICKED, 
      new MsgHandlerFunction<RedWindow>(this, OnButtonClicked));
}

void FC RedWindow::OnDrawWindow(DGWindowSurface* surface)
{
   surface->FillSurface(DGColor(255, 0, 0));
}

void FC RedWindow::OnWindowSized()
{
   DGPoint size = GetSize();

   int labelWidth = size.x - (2 * LABEL_OFFSET_X);

   if(labelWidth < 0)
      labelWidth = 0;

   titleBar->SetDimensions(DGArea(0, 0, size.x, TITLEBAR_HEIGHT));
   testLabel->SetDimensions(DGArea(LABEL_OFFSET_X, TITLEBAR_HEIGHT + 
      LABEL_OFFSET_Y, labelWidth, LABEL_HEIGHT));

   DGPoint buttonSize = testButton->GetSize();
   testButton->SetPosition((size.x / 2) - (buttonSize.x / 2), 
      ((size.y * 2) / 3) - (buttonSize.y / 2));

   DGPoint resizeSize = resizeCtrl->GetSize();
   resizeCtrl->SetPosition(DGPoint(size.x - resizeSize.x, 
      size.y - resizeSize.y));
}

void RedWindow::OnButtonClicked(DGMessage* msg)
{
   if(msg->data3 == IDB_TESTBUTTON)
   {
      DGColor randomColor(rand() % 256, rand() % 256, rand() % 256);
      ((BlueWindow*)GetParent())->SetBackgroundColor(randomColor);
   }
}
