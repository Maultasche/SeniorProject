/*------------------------------------------------------------------------
File Name: DGMainWindow.cpp
Description: This file contains the implementation of the DGMainWindow 
   class, which represents the main window in the GUI and is at the top 
   of the window hierarchy.
Version:
   1.0.0    25.04.2001  Created the file
------------------------------------------------------------------------*/


#include "DxGuiFramework.h"

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   UINT winID : the ID of the window to be constructed
   bool control : whether the window is a control or not
Description:
   This function constructs the DGMainWindow object.
------------------------------------------------------------------------*/

DGMainWindow::DGMainWindow(UINT winID, bool control) :
   DGWindow(winID, control)
{
   windowType = WT_MAINWINDOW;
}

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   UINT winID : the ID of the window to be constructed
   bool control : whether the window is a control or not
   DGArea dimensions : the dimensions of the window to be constructed
Description:
   This function constructs the DGMainWindow object.
------------------------------------------------------------------------*/

DGMainWindow::DGMainWindow(UINT winID, bool control, 
                           DGRectangle dimensions) :
   DGWindow(winID, control, dimensions)
{
   windowType = WT_MAINWINDOW;
}

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   UINT winID : the ID of the window to be constructed
   bool control : whether the window is a control or not
   DGPoint position : the position of the window to be constructed
   DGPoint size : the size of the window to be constructed
Description:
   This function constructs the DGMainWindow object.
------------------------------------------------------------------------*/

DGMainWindow::DGMainWindow(UINT winID, bool control, 
                           DGPoint position, DGPoint size) :
   DGWindow(winID, control, position, size)
{
   windowType = WT_MAINWINDOW;
}

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   UINT winID : the ID of the window to be constructed
   bool control : whether the window is a control or not
   int xPos : the x-coordinate of the position of the window
   int yPos : the y-coordinate of the position of the window
   int width : the width of the window
   int height : the height of the window
Description:
   This function constructs the DGMainWindow object.
------------------------------------------------------------------------*/

DGMainWindow::DGMainWindow(UINT winID, bool control, int xPos, int yPos,
                           int width, int height) :
   DGWindow(winID, control, xPos, yPos, width, height)
{
   windowType = WT_MAINWINDOW;
}

/*Destructor*/
DGMainWindow::~DGMainWindow()
{

}

//Overridden Member Functions

/*------------------------------------------------------------------------
Function Name: SetPosition
Parameters:
   const DGPoint& position : a DGPoint object describing a new window
      position
Description:
   This overridden function simply sets the window to position (0, 0).
------------------------------------------------------------------------*/

void FC DGMainWindow::SetPosition(DGPoint& position)
{
   DGWindow::SetPosition(0, 0);
}

/*------------------------------------------------------------------------
Function Name: SetPosition
Parameters:
   int xPos : the x-coordinate of the new window position
   int yPos : the y-coordinate of the new window position
Description:
   This overridden function simply sets the window to position (0, 0).
------------------------------------------------------------------------*/

void FC DGMainWindow::SetPosition(int xPos, int yPos)
{
   DGWindow::SetPosition(0, 0);
}

/*------------------------------------------------------------------------
Function Name: SetSize
Parameters:
   const DGPoint& size : a DGPoint object describing a new window
      size
Description:
   This overridden function resizes the window to the size of the screen
------------------------------------------------------------------------*/

void FC DGMainWindow::SetSize(DGPoint& size)
{
   DGPoint res = dgGraphics->GetResolution();
   DGWindow::SetSize(res);
}

/*------------------------------------------------------------------------
Function Name: SetSize
Parameters:
   int width : the new width of the window
   int height : the new height of the window
Description:
   This overridden function resizes the window to the size of the screen
------------------------------------------------------------------------*/

void FC DGMainWindow::SetSize(int width, int height)
{
   DGPoint res = dgGraphics->GetResolution();
   DGWindow::SetSize(res);
}

/*------------------------------------------------------------------------
Function Name: SetDimensions
Parameters:
   const DGArea& dimensions : a DGArea object describing a new window
      position and size
Description:
   This overridden function sets the window position to (0, 0) and the 
   window size to be the same as that of the screen.
------------------------------------------------------------------------*/

void FC DGMainWindow::SetDimensions(DGArea& dimensions)
{
   DGPoint res = dgGraphics->GetResolution();
   DGWindow::SetDimensions(0, 0, res.x, res.y);
}

/*------------------------------------------------------------------------
Function Name: SetDimensions
Parameters:
   const DGPoint& position : a DGPoint object describing a new window
      position
   const DGPoint& size : a DGPoint object describing a new window
      size
Description:
   This overridden function sets the window position to (0, 0) and the 
   window size to be the same as that of the screen.
------------------------------------------------------------------------*/

void FC DGMainWindow::SetDimensions(DGPoint& position, DGPoint& size)
{
   DGPoint res = dgGraphics->GetResolution();
   DGWindow::SetDimensions(0, 0, res.x, res.y);
}

/*------------------------------------------------------------------------
Function Name: SetDimensions
Parameters:
   int x : the x-coordinate of the new window position
   int y : the y-coordinate fo the new window position
   width : the new window width
   height : the new window height
Description:
   This overridden function sets the window position to (0, 0) and the 
   window size to be the same as that of the screen.
------------------------------------------------------------------------*/

void FC DGMainWindow::SetDimensions(int x, int y, int width, int height)
{
   DGPoint res = dgGraphics->GetResolution();
   DGWindow::SetDimensions(0, 0, res.x, res.y);
}

/*------------------------------------------------------------------------
Function Name: HideWindow
Parameters:
Description:
   This overridden function does nothing
------------------------------------------------------------------------*/

void FC DGMainWindow::HideWindow(void)
{
   //Do Nothing
}

/*------------------------------------------------------------------------
Function Name: ShowWindow
Parameters:
Description:
   This overridden function does nothing
------------------------------------------------------------------------*/

void FC DGMainWindow::ShowWindow(void)
{
   //Do Nothing
}

//Overridden Message Handlers

/*------------------------------------------------------------------------
Function Name: OnWindowResize
Parameters:
   int xPos - the x-coordinate of the new window position
   int yPos - the y-coordinate of the new window position
Description:
   This overridden function does nothing
------------------------------------------------------------------------*/

void FC DGMainWindow::OnWindowReposition(int xPos, int yPos)
{
   //Do Nothing
}

/*------------------------------------------------------------------------
Function Name: OnWindowResize
Parameters:
   int width - the new width of the window
   int height - the new height of the window
Description:
   This overridden function does nothing
------------------------------------------------------------------------*/

void FC DGMainWindow::OnWindowResize(int width, int height)
{
   //Do Nothing
}
