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
   void FC OnMouseMove(int x, int y, BYTE* keyboardState);
   void FC OnWindowSized(void);

   void OnLoadBitmap(DGMessage* msg);
   void OnSBLineUp(DGMessage* msg);
   void OnSBLineDown(DGMessage* msg);

private:
   DGPoint previousPosition;

   bool windowFocused;
   bool windowMoving;

   DGImage* imageCtrl;
   DGEdit* inputCtrl;
   DGTitleBar* titleBar;
   DGResize* resizeCtrl;
   DGButton* loadButton;
   DGScrollBar* horizontalBar;
   DGScrollBar* verticalBar;
};

#endif