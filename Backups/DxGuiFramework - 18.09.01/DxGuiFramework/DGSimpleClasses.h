/*------------------------------------------------------------------------
File Name: DGGraphics.h
Description: This file contains various simple data storage classes
   that are used throughout the application.
Version:
   1.0.0    10.02.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGSIMPLECLASSES_H
#define DGSIMPLECLASSES_H

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

   void SetPoint(int xPos, int yPos)
   {
      x = xPos;
      y = yPos;
   }

   void Offset(int dx, int dy)
   {
      x += dx;
      y += dy;
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
      //assert(rect.left <= rect.right && rect.top <= rect.bottom);
      left = rect.left;
      top = rect.top;
      right = rect.right;
      bottom = rect.bottom;
   }

   DGRectangle(DGPoint& ulCorner, DGPoint& lrCorner)
   {
      //assert(ulCorner.x <= lrCorner.x && ulCorner.y <= lrCorner.y);
      left = ulCorner.x;
      top = ulCorner.y;
      right = lrCorner.x;
      bottom = lrCorner.y;
   }

   DGRectangle(int lt, int tp, int rt, int bt)
   {
      //assert(lt <= rt && tp <= bt);
      left = lt;
      top = tp;
      right = rt;
      bottom = bt;
   }

   int Width(void) {return (right - left) + 1;}
   int Height(void) {return (bottom - top) + 1;}

   void SetRectangle(DGPoint& ulCorner, DGPoint& lrCorner)
   {
      //assert(ulCorner.x <= lrCorner.x && ulCorner.y <= lrCorner.y);
      left = ulCorner.x;
      top = ulCorner.y;
      right = lrCorner.x;
      bottom = lrCorner.y;
   }

   void SetRectangle(int lt, int tp, int rt, int bt)
   {
      //assert(lt <= rt && tp <= bt);
      left = lt;
      top = tp;
      right = rt;
      bottom = bt;
   }
 
   bool IsInRect(DGPoint& point)
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

   void Offset(int dx, int dy)
   {
      left += dx;
      right += dx;
      top += dy;
      bottom += dy;
   }
};

class DGArea
{
public:
   int left;
   int top;
   int width;
   int height;

   DGArea() 
   {
      top = 0;
      left = 0;
      width = 0;
      height = 0;
   }

   DGArea(DGArea& area)
   {
      left = area.left;
      top = area.top;
      width = area.width;
      height = area.height;
   }

   DGArea(DGRectangle& rect)
   {
      left = rect.left;
      top = rect.top;
      width = rect.Width();
      height = rect.Height();
   }

   DGArea(DGPoint& ulCorner, DGPoint& widthHeight)
   {
      left = ulCorner.x;
      top = ulCorner.y;
      width = widthHeight.x;
      height = widthHeight.y;
   }

   DGArea(int lt, int tp, int w, int h)
   {
      left = lt;
      top = tp;
      width = w;
      height = h;
   }

   int Right(void) {return (left + width) - 1;}
   int Bottom(void) {return (top + height) - 1;}

   void SetArea(DGPoint& ulCorner, DGPoint& widthHeight)
   {
      left = ulCorner.x;
      top = ulCorner.y;
      width = widthHeight.x;
      height = widthHeight.y;
   }

   void SetArea(int lt, int tp, int w, int h)
   {
      left = lt;
      top = tp;
      width = w;
      height = h;
   }

   bool IsInArea(DGPoint& point)
   {
      if(point.x >= left && point.y >= top &&
         point.x <= Right() && point.y <= Bottom())
         return true;
      else
         return false;
   }

   bool IsInArea(int x, int y)
   {
      if(x >= left && y >= top &&
         x <= Right() && y <= Bottom())
         return true;
      else
         return false;
   }

   RECT ToRECT(void)
   {
      RECT rect = {left, top, Right(), Bottom()};
      return rect;
   }

   void Offset(int dx, int dy)
   {
      left += dx;
      top += dy;
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

//The following is a functor, used to call member function callbacks
class DGMessage;

// abstract base class
class MsgHandlerInterface
{
public:
   // two possible functions to call member function. virtual cause derived
   // classes will use a pointer to an object and a pointer to a member function
   // to make the function call
   virtual void operator()(DGMessage* msg) {}  // call using operator
   virtual void Call(DGMessage* msg) {}       // call using function
};

template <class TClass>
class MsgHandlerFunction : public MsgHandlerInterface
{
public:
   MsgHandlerFunction(TClass* object, void (TClass::*function)(DGMessage*))
   {
      objectPointer = object;
      functionPointer = function;
   }

   // override operator "()"
   virtual void operator()(DGMessage* msg)
   { 
      (*objectPointer.*functionPointer)(msg);
   }

   // override function "Call"
   virtual void Call(DGMessage* msg)
   { 
      (*objectPointer.*functionPointer)(msg);
   } 

private:
   void (TClass::*functionPointer)(DGMessage*);
   TClass* objectPointer;
};

#endif