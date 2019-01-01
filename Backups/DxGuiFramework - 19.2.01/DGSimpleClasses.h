/*------------------------------------------------------------------------
File Name: DGGraphics.h
Description: This file contains various simple data storage classes
   that are used throughout the application.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#ifndef DGSIMPLECLASSES_H
#define DGSIMPLECLASSES_H

class DGColor
{
public:
   BYTE r;
   BYTE g;
   BYTE b;

   DGColor(BYTE red, BYTE green, BYTE blue)
   {
      r = red;
      g = green;
      b = blue;
   }

   USHORT To16Bit5(void)
   {
      return ((b >> 3)+((g & 248) << 2)+((r & 248) << 7));
   }

   USHORT To16Bit6(void)
   {
      return ((b >> 3)+((g & 252) << 2)+((r & 248) << 8));
   }

   UINT To32Bit(void)
   {
      return ((r << 16) + (g << 8) + b);
   }
};

class DGFont
{

};

class DGPoint
{
public:
   int x;
   int y;

   DGPoint()
   {
      x = 0;
      y = 0;
   }

   DGPoint(int xPos, int yPos)
   {
      x = xPos;
      y = yPos;
   }
};

class DGRectangle
{
public:
   int left;
   int top;
   int right;
   int bottom;

   DGRectangle() 
   {
      top = 0;
      left = 0;
      right = 0;
      bottom = 0;
   }

   DGRectangle(DGRectangle& rect)
   {
      left = rect.left;
      top = rect.top;
      right = rect.right;
      bottom = rect.bottom;
   }

   DGRectangle(DGPoint& ulCorner, DGPoint& lrCorner)
   {
      left = ulCorner.x;
      top = ulCorner.y;
      right = lrCorner.x;
      bottom = lrCorner.y;
   }

   DGRectangle(int lt, int tp, int rt, int bt)
   {
      left = lt;
      top = tp;
      right = rt;
      bottom = bt;
   }

   int Width(void) {return (right - left) + 1;}
   int Height(void) {return (bottom - top) + 1;}

   bool IsInRect(DGPoint point)
   {
      if(point.x >= left && point.y >= top &&
         point.x <= right && point.y <= bottom)
         return true;
      else
         return false;
   }

   bool IsInRect(int x, int y)
   {
      if(x >= left && y >= top &&
         x <= right && y <= bottom)
         return true;
      else
         return false;
   }

   RECT ToRECT(void)
   {
      RECT rect = {left, top, right, bottom};
      return rect;
   }
};

class DGWindowSettings
{
public:
   char windowName[128];    // window name
   DWORD dwStyle;           // window style
   int xPos;                // horizontal position of window
   int yPos;                // vertical position of window
   int nWidth;           // window width
   int nHeight;          // window height
   HMENU hMenu;          // handle to menu or child-window identifier
};
#endif