/*GreenWindow.cpp*/

#include <DxGuiFramework.h>
#include "DxGuiTestApp.h"
#include "GreenWindow.h"

#define  IMAGE_OFFSET_X       40
#define  IMAGE_OFFSET_Y       10
#define  INPUT_OFFSET_Y       20
#define  INPUT_SIZE_Y         24
              
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
   imageCtrl = new DGImage(IDI_IMAGE, this, DGArea(40, 10, 220, 200),
      IDB_IMAGEBITMAP);

   imageCtrl->LoadBitmapFile("Bitmaps/Stones Large.bmp");
   //imageCtrl->LoadBitmapFile("Bitmaps/persview.bmp");
   //imageCtrl->LoadBitmapFile("Bitmaps/stars.bmp");

   //imageCtrl->SetTransparency(true);
   //imageCtrl->SetTransparentColor(DGColor(0, 0, 255));

   inputCtrl = new DGEdit(IDE_IMAGENAME, this, DGArea(100, 220, 100, 24),
      "Bitmap.bmp");

   AddChildWindow(imageCtrl);
   AddChildWindow(inputCtrl);
}

void FC GreenWindow::OnDrawWindow(DGWindowSurface* surface)
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
      surface->FillSurface(DGColor(80, 180, 120));

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

void FC GreenWindow::OnMouseEnter(int x, int y, BYTE* keyboardState)
{
   DGGetGui()->SetWindowFocus(GetWindowID());
}

void FC GreenWindow::OnSetFocus(UINT winID)
{
   windowFocused = true;
}

void FC GreenWindow::OnLoseFocus(UINT winID)
{
   windowFocused = false;
}

void FC GreenWindow::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   //We need to keep track of the mouse movement in absolute coords
   //Relative coords will always be the same when it is moving
   previousPosition = RelToAbsCoords(x, y);
   windowMoving = true;
   DGGetGui()->SetMouseCapture(GetWindowID());
   SetChildWindowDraw(false);
}

void FC GreenWindow::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   windowMoving = false;
   DGGetGui()->ReleaseMouseCapture();
   SetChildWindowDraw(true);
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

   imageCtrl->SetDimensions(DGArea(IMAGE_OFFSET_X, IMAGE_OFFSET_Y, 
      size.x - IMAGE_OFFSET_X - 1, (2 * size.y / 3)));

   //inputCtrl->SetDimensions(DGArea(
}
