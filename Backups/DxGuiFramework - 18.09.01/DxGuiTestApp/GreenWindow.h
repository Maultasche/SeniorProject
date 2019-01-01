/*GreenWindow.h*/

#ifndef GREENWINDOW_H
#define GREENWINDOW_H

class GreenWindow : public DGWindow
{
public:
   GreenWindow();
   GreenWindow(int xPos, int yPos, int width, int height);

protected:
   void FC OnCreate(void);
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnMouseEnter(int x, int y, BYTE* keyboardState);
   void FC OnSetFocus(UINT winID);
   void FC OnLoseFocus(UINT winID);
   void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnMouseMove(int x, int y, BYTE* keyboardState);
   void FC OnWindowSized(void);

private:
   DGPoint previousPosition;

   bool windowFocused;
   bool windowMoving;

   DGImage* imageCtrl;
   DGEdit* inputCtrl;
};

#endif