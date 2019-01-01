/*------------------------------------------------------------------------
File Name: DGResize.cpp
Description: This file contains the implementation of the DGResize class, 
   which is a control that allows the user to resize a window.
Version:
   1.0.0    23.09.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"


DGResize::DGResize(UINT winID, DGWindow* parentWin) :
   DGWindow(winID, true, 0, 0, RESIZE_CONTROL_SIZE_X,
      RESIZE_CONTROL_SIZE_Y),
   resizing(false)
{
   SetWindowType(WT_RESIZE);
   //SetParent(parentWin);

   //If the resize bitmap is not loaded, then load it
   DGBitmap* bitmap = dgGraphics->GetBitmap(IDB_RESIZE);
   if(bitmap == NULL)
   {
      dgGraphics->LoadBitmap(IDB_RESIZE, 1, "Bitmaps/ResizeControl.bmp");
      bitmap = dgGraphics->GetBitmap(IDB_RESIZE);
      bitmap->SetTransparentColor(DGColor(255, 255, 255));
   }
}

void FC DGResize::OnCreate()
{
   DGPoint parentSize = GetParent()->GetSize();
   DGPoint size = GetSize();

   SetPosition(parentSize.x - size.x, parentSize.y - size.y); 
}

void FC DGResize::OnDrawWindow(DGWindowSurface* surface)
{
   surface->DrawBitmap(DGPoint(0, 0), IDB_RESIZE);
   //surface->DrawTransparentBitmap(DGPoint(0, 0), IDB_RESIZE,
   //   DGColor(255, 255, 255));
}

void FC DGResize::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   //We need to keep track of the mouse movement in absolute coords
   //Relative coords will always be the same when it is moving
   previousPosition = RelToAbsCoords(x, y);
   DGGetGui()->SetMouseCapture(GetWindowID());

   resizing = true;
}

void FC DGResize::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   DGGetGui()->ReleaseMouseCapture();

   resizing = false;
}

void FC DGResize::OnMouseMove(int x, int y, BYTE* keyboardState)
{
   if(resizing)
   {
      //Translate the current position of the mouse to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      DGPoint mouseMovement(absoluteCoords.x - previousPosition.x, 
         absoluteCoords.y - previousPosition.y);

      previousPosition = absoluteCoords;

      //Change the size of the parent relative to how the mouse
      //cursor moved
      DGPoint parentWindowSize = GetParent()->GetSize();
      DGPoint windowSize = GetSize();
      parentWindowSize.Offset(mouseMovement.x, mouseMovement.y);

      if(parentWindowSize.x < windowSize.x)
         parentWindowSize.x = windowSize.x;
      if(parentWindowSize.y < windowSize.y)
         parentWindowSize.y = windowSize.y;

      GetParent()->SetSize(parentWindowSize);
   }
}

