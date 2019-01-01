/*BlueWindow.h*/

#ifndef BLUEWINDOW_H
#define BLUEWINDOW_H

class BlueWindow : public DGMainWindow
{
public:
   BlueWindow();
   ~BlueWindow();

   void SetBackgroundColor(DGColor color) {backgroundColor = color;}
   DGColor GetBackgroundColor(void) {return backgroundColor;}

protected:
   void FC OnCreate(void);
   void FC OnDrawWindow(DGWindowSurface* surface);

private:
   bool windowFocused;

   DGColor backgroundColor;
};

#endif