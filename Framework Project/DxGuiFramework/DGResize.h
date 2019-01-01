/*------------------------------------------------------------------------
File Name: DGResize.h
Description: This file contains the DGResize class, which is a control 
   that allows the user to resize a window.
Version:
   1.0.0    23.09.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGRESIZE_H
#define DGRESIZE_H

#define RESIZE_CONTROL_SIZE_X      16
#define RESIZE_CONTROL_SIZE_Y      16

class DGResize : public DGWindow
{
public:
   DGResize(UINT winID, DGWindow* parentWin);

protected:
   void FC OnCreate();
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnMouseMove(int x, int y, BYTE* keyboardState);

private:
   DGPoint previousPosition;
   bool resizing;
};

#endif