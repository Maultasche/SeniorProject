/*BlueWindow.cpp*/

#include <DxGuiFramework.h>
#include "DxGuiTestApp.h"
#include "RedWindow.h"
#include "BlueWindow.h"
//#include "YellowWindow.h"
#include "GreenWindow.h"

BlueWindow::BlueWindow() : DGMainWindow(IDW_BLUEWINDOW, false)
{
   windowFocused = false;
}

BlueWindow::~BlueWindow()
{

}

void FC BlueWindow::OnCreate()
{
   //Create the child windows
   AddChildWindow(new RedWindow(100, 100, 200, 200));
   AddChildWindow(new GreenWindow(150, 150, 300, 300));
}

void FC BlueWindow::OnDrawWindow(DGWindowSurface* surface)
{
   surface->FillSurface(DGColor(0, 0, 255));
   if(windowFocused)
   {
      DGPoint size = GetSize();
      surface->LockSurface();
      surface->DrawRectangle(DGRectangle(0, 0, size.x - 1, size.y - 1), 
         DGColor(255, 255, 255));
      surface->DrawRectangle(DGRectangle(1, 1, size.x - 2, size.y - 2), 
         DGColor(255, 255, 255));
      surface->UnlockSurface();
   }
}

void FC BlueWindow::OnMouseEnter(int x, int y, BYTE* keyboardState)
{
   DGGetGui()->SetWindowFocus(GetWindowID());
}

void FC BlueWindow::OnSetFocus(UINT winID)
{
   windowFocused = true;
}

void FC BlueWindow::OnLoseFocus(UINT winID)
{
   windowFocused = false;
}
