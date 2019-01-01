/*RedWindow.h*/

#ifndef REDWINDOW_H
#define REDWINDOW_H

class RedWindow : public DGWindow
{
public:
   RedWindow();
   RedWindow(int xPos, int yPos, int width, int height);

protected:
   void FC OnCreate(void);
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnWindowSized(void);

   //Non-overridden message handling methods
   void OnButtonClicked(DGMessage* msg);

private:
   DGPoint previousPosition;

   bool windowFocused;
   bool windowMoving;

   DGLabel* testLabel;
   DGButton* testButton;
   DGTitleBar* titleBar;
   DGResize* resizeCtrl;
};

#endif