/*BlueWindow.h*/

#ifndef BLUEWINDOW_H
#define BLUEWINDOW_H

class BlueWindow : public DGMainWindow
{
public:
   BlueWindow();
   ~BlueWindow();

protected:
   void FC OnCreate(void);
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnMouseEnter(int x, int y, BYTE* keyboardState);
   void FC OnSetFocus(UINT winID);
   void FC OnLoseFocus(UINT winID);


private:
   bool windowFocused;

};

#endif