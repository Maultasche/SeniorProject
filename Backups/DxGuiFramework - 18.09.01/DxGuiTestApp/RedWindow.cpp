/*RedWindow.cpp*/

#include <DxGuiFramework.h>
#include "DxGuiTestApp.h"
#include "RedWindow.h"

RedWindow::RedWindow() : DGWindow(IDW_REDWINDOW, false)
{
   windowFocused = false;
   windowMoving = false;
}

RedWindow::RedWindow(int xPos, int yPos, int width, int height) :
   DGWindow(IDW_REDWINDOW, false, xPos, yPos, width, height)
{
   windowFocused = false;
   windowMoving = false;
}

void FC RedWindow::OnCreate()
{
   testLabel = new DGLabel(IDL_TESTLABEL, this, DGArea(10, 0, 180, 60),
      "Click the button to change the background color", true, 
      DGColor(0, 0, 0), DGColor(255, 0, 0),
      DT_CENTER | DT_WORDBREAK);
 
   testButton = new DGButton(IDB_TESTBUTTON, this, DGArea(75, 110, 50, 30));

   AddChildWindow(testLabel);
   AddChildWindow(testButton);

   AddMessageHandler(GM_LABEL_LBUTTONDOWN, 
      new MsgHandlerFunction<RedWindow>(this, OnLabelLButtonDown));
}

void FC RedWindow::OnDrawWindow(DGWindowSurface* surface)
{
   if(windowMoving)
   {
      DGPoint size = GetSize();
      surface->LockSurface();
      surface->DrawRectangle(DGRectangle(0, 0, size.x - 1, size.y - 1), 
         DGColor(255, 255, 255));
      surface->DrawRectangle(DGRectangle(1, 1, size.x - 2, size.y - 2), 
         DGColor(255, 255, 255));
      surface->UnlockSurface();
   } 

   else
      surface->FillSurface(DGColor(255, 0, 0));

   if(windowFocused)
   {
      DGPoint size = GetSize();
      surface->LockSurface();
      surface->DrawRectangle(DGRectangle(0, 0, size.x - 1, size.y - 1), 
         DGColor(255, 255, 255));
      surface->DrawRectangle(DGRectangle(1, 1, size.x - 2, size.y - 2), 
         DGColor(255, 255, 255));
      surface->UnlockSurface();
   }
}

void FC RedWindow::OnMouseEnter(int x, int y, BYTE* keyboardState)
{
   DGGetGui()->SetWindowFocus(GetWindowID());
}

void FC RedWindow::OnSetFocus(UINT winID)
{
   windowFocused = true;
}

void FC RedWindow::OnLoseFocus(UINT winID)
{
   windowFocused = false;
}

void FC RedWindow::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   //We need to keep track of the mouse movement in absolute coords
   //Relative coords will always be the same when it is moving
   previousPosition = RelToAbsCoords(x, y);
   windowMoving = true;
   DGGetGui()->SetMouseCapture(GetWindowID());
   SetChildWindowDraw(false);

#ifdef _DEBUG
   char debugString[256];
   sprintf(debugString, "Red Window - Left Button Down: %i,%i", 
      previousPosition.x, previousPosition.y);
   debugLog.LogString(debugString);
#endif
}

void FC RedWindow::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   windowMoving = false;
   DGGetGui()->ReleaseMouseCapture();
   SetChildWindowDraw(true);
}  

void FC RedWindow::OnMouseMove(int x, int y, BYTE* keyboardState)
{
   if(windowMoving)
   {
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      DGPoint windowMovement(absoluteCoords.x - previousPosition.x, 
         absoluteCoords.y - previousPosition.y);

#ifdef _DEBUG
      char debugString[256];
      sprintf(debugString, "Red Window - Moving: %i,%i\n", 
         absoluteCoords.x, absoluteCoords.y);
      debugLog.LogString(debugString);
      sprintf(debugString, "Previous Coords: %i,%i\n",
         previousPosition.x, previousPosition.y);
      debugLog.LogString(debugString);
      sprintf(debugString, "Window Movement: %i,%i\n",
         windowMovement.x, windowMovement.y);
      debugLog.LogString(debugString);
#endif

      previousPosition = absoluteCoords;

      //Change the position of the window relative to how the mouse
      //cursor moved
      DGPoint windowPosition = GetPosition();
      windowPosition.Offset(windowMovement.x, windowMovement.y);
      SetPosition(windowPosition);
      

#ifdef _DEBUG
      sprintf(debugString, "New Position: %i, %i\n",
         windowPosition.y, windowPosition.y);
      debugLog.LogString(debugString);
#endif
   }
}

void RedWindow::OnLabelLButtonDown(DGMessage* msg)
{
   OutputDebugString("Label Clicked\n");
}
