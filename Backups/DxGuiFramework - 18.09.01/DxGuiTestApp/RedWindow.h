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
   void FC OnMouseEnter(int x, int y, BYTE* keyboardState);
   void FC OnSetFocus(UINT winID);
   void FC OnLoseFocus(UINT winID);
   void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnMouseMove(int x, int y, BYTE* keyboardState);

   //Non-overridden message handling methods
   void OnLabelLButtonDown(DGMessage* msg);

private:
   DGPoint previousPosition;

   bool windowFocused;
   bool windowMoving;

   DGLabel* testLabel;
   DGButton* testButton;

#ifdef _DEBUG
   DGDebugLog debugLog;
#endif
};

#endif