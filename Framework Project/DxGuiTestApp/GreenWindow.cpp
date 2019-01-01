/*GreenWindow.cpp*/

#include <DxGuiFramework.h>
#include "DxGuiTestApp.h"
#include "GreenWindow.h"

#define  IMAGE_OFFSET_X       40
#define  IMAGE_OFFSET_Y       10
#define  INPUT_OFFSET_Y       20
#define  INPUT_SIZE_Y         24
#define  TITLEBAR_HEIGHT      20
#define  INPUT_BUTTON_GAP     10
#define  SCROLLBAR_WIDTH      16
#define  SCROLLBAR_LINE_VAL   10
              
GreenWindow::GreenWindow() : DGWindow(IDW_GREENWINDOW, false)
{
   windowFocused = false;
   windowMoving = false;
}

GreenWindow::GreenWindow(int xPos, int yPos, int width, int height) :
   DGWindow(IDW_GREENWINDOW, false, xPos, yPos, width, height)
{
   windowFocused = false;
   windowMoving = false;
}

void FC GreenWindow::OnCreate()
{
   DGWindow::OnCreate();

   imageCtrl = new DGImage(IDI_IMAGE, this, DGArea(40, 10, 220, 200),
      IDB_IMAGEBITMAP);

   //imageCtrl->LoadBitmapFile("Bitmaps/Stones Large.bmp");
   imageCtrl->LoadBitmapFile("Bitmaps/persview.bmp");
   //imageCtrl->LoadBitmapFile("Bitmaps/stars.bmp");

   //imageCtrl->SetTransparency(true);
   //imageCtrl->SetTransparentColor(DGColor(0, 0, 255));

   inputCtrl = new DGEdit(IDE_IMAGENAME, this, DGArea(100, 220, 100, 24),
      "Bitmap.bmp");

   titleBar = new DGTitleBar(IDC_GREEN_TITLEBAR, this, 
      DGArea(0, 0, 300, TITLEBAR_HEIGHT), "Green Window",
      DGFont("MS Sans Serif", 16));

   resizeCtrl = new DGResize(IDC_GREEN_RESIZE, this);

   loadButton = new DGButton(IDC_LOADBUTTON, this, DGArea(220, 220, 50, 24),
      BT_PUSHBUTTON | BT_TEXTBUTTON, "Load", DGFont("MS Sans Serif", 16));

   horizontalBar = new DGScrollBar(IDC_SB_HORIZONTAL, this, 
      DGArea(40, 210, 220, 16), 0, imageCtrl->GetBitmapSize().x,
      SB_HORIZONTAL);

   verticalBar = new DGScrollBar(IDC_SB_VERTICAL, this, 
      DGArea(240, 10, 16, 200), 0, imageCtrl->GetBitmapSize().y,
      SB_VERTICAL);

   horizontalBar->SetLineValue(SCROLLBAR_LINE_VAL);
   verticalBar->SetLineValue(SCROLLBAR_LINE_VAL);

   AddChildWindow(imageCtrl);
   AddChildWindow(inputCtrl);
   AddChildWindow(titleBar);
   AddChildWindow(resizeCtrl);
   AddChildWindow(loadButton);
   AddChildWindow(horizontalBar);
   AddChildWindow(verticalBar);

   AddMessageHandler(GM_BUTTON_CLICKED, 
      new MsgHandlerFunction<GreenWindow>(this, OnLoadBitmap));

   AddMessageHandler(GM_EDIT_ENTER, 
      new MsgHandlerFunction<GreenWindow>(this, OnLoadBitmap));

   AddMessageHandler(GM_SCROLLBAR_LINEUP, 
      new MsgHandlerFunction<GreenWindow>(this, OnSBLineUp));

   AddMessageHandler(GM_SCROLLBAR_LINEDOWN, 
      new MsgHandlerFunction<GreenWindow>(this, OnSBLineDown));
}

void FC GreenWindow::OnDrawWindow(DGWindowSurface* surface)
{
   surface->FillSurface(DGColor(80, 180, 120));
}

void FC GreenWindow::OnMouseMove(int x, int y, BYTE* keyboardState)
{
   if(windowMoving)
   {
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      DGPoint windowMovement(absoluteCoords.x - previousPosition.x, 
         absoluteCoords.y - previousPosition.y);

      previousPosition = absoluteCoords;

      //Change the position of the window relative to how the mouse
      //cursor moved
      DGPoint windowPosition = GetPosition();
      windowPosition.Offset(windowMovement.x, windowMovement.y);
      SetPosition(windowPosition);
   }
}

void FC GreenWindow::OnWindowSized()
{
   DGPoint size = GetSize();

   int imageCtrlWidth = size.x - (IMAGE_OFFSET_X * 2) - 1;

   if(imageCtrlWidth < 0)
      imageCtrlWidth = 0;

   imageCtrl->SetDimensions(DGArea(IMAGE_OFFSET_X, IMAGE_OFFSET_Y + TITLEBAR_HEIGHT, 
      imageCtrlWidth, (2 * size.y / 3)));

   int inputCtrlWidth = size.x / 2;
   int inputPositionX = size.x / 8; 
   int inputPositionY = size.y - INPUT_SIZE_Y - INPUT_OFFSET_Y;

   inputCtrl->SetDimensions(DGArea(inputPositionX, inputPositionY, 
      inputCtrlWidth, INPUT_SIZE_Y));

   titleBar->SetDimensions(DGArea(0, 0, size.x, TITLEBAR_HEIGHT));

   DGPoint resizeSize = resizeCtrl->GetSize();
   resizeCtrl->SetPosition(DGPoint(size.x - resizeSize.x, size.y - resizeSize.y));

   loadButton->SetPosition(inputPositionX + inputCtrlWidth + INPUT_BUTTON_GAP,
      inputPositionY);

   //This is so we don't have a scroll bar less than 1 pixel, which causes an
   //assertion failure in the graphics engine when the surface is filled
   if(imageCtrlWidth == 0)
      imageCtrlWidth++;

   horizontalBar->SetDimensions(DGArea(IMAGE_OFFSET_X, 
      IMAGE_OFFSET_Y + TITLEBAR_HEIGHT + imageCtrl->GetSize().y, 
      imageCtrlWidth, SCROLLBAR_WIDTH));

   verticalBar->SetDimensions(DGArea(IMAGE_OFFSET_X + imageCtrlWidth, 
      IMAGE_OFFSET_Y + TITLEBAR_HEIGHT, SCROLLBAR_WIDTH, imageCtrl->GetSize().y));
}

void GreenWindow::OnLoadBitmap(DGMessage* msg)
{
   if(msg->data3 == IDC_LOADBUTTON || msg->data3 == IDE_IMAGENAME)
   {
      //Get the file name from the edit control
      const char* fileName = inputCtrl->GetText();

      if(!dgGraphics->BitmapFileExists(fileName))
      {
         char errorMsg[300];
         sprintf(errorMsg, "The file %s could not be found.", fileName);
         ::MessageBox(DGGetApp()->GetWindowsHandle(), errorMsg, "File Not Found",
            MB_OK | MB_ICONERROR);
      }

      else
      {
         imageCtrl->LoadBitmapFile(fileName);
         
         //Set the ranges on the scroll bars
         DGPoint bitmapSize = imageCtrl->GetBitmapSize();
         DGPoint imageCtrlSize = imageCtrl->GetSize();

         horizontalBar->SetMinValue(0);
         horizontalBar->SetPosition(0);
         verticalBar->SetMinValue(0);
         verticalBar->SetPosition(0);

         //If the bitmap is smaller than the image control, set the max value
         //of the scroll bar to 0
         if(bitmapSize.x < imageCtrlSize.x)
            horizontalBar->SetMaxValue(0);
         else
            horizontalBar->SetMaxValue(imageCtrlSize.x - bitmapSize.x);

         if(bitmapSize.y < imageCtrlSize.y)
            verticalBar->SetMaxValue(0);
         else
            verticalBar->SetMaxValue(imageCtrlSize.y - bitmapSize.y);
      }
   }
}

void GreenWindow::OnSBLineUp(DGMessage* msg)
{
   if(msg->data3 == IDC_SB_HORIZONTAL || msg->data3 == IDC_SB_VERTICAL)
   {
      int xPosition = horizontalBar->GetPosition();
      int yPosition = verticalBar->GetPosition();
      
      char outputString[256];
      sprintf(outputString, "Setting Position (%i, %i)\n", xPosition, yPosition);
      OutputDebugString(outputString);

      imageCtrl->SetBitmapOrigin(DGPoint(-xPosition, -yPosition));
   }
}

void GreenWindow::OnSBLineDown(DGMessage* msg)
{
   if(msg->data3 == IDC_SB_HORIZONTAL || msg->data3 == IDC_SB_VERTICAL)
   {
      int xPosition = horizontalBar->GetPosition();
      int yPosition = verticalBar->GetPosition();

      char outputString[256];
      sprintf(outputString, "Setting Position (%i, %i)\n", xPosition, yPosition);
      OutputDebugString(outputString);

      imageCtrl->SetBitmapOrigin(DGPoint(-xPosition, -yPosition));
   }
}
