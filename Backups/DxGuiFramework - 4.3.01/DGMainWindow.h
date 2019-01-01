/*------------------------------------------------------------------------
File Name: DGMainWindow.h
Description: This file contains the DGMainWindow class, which represent
   the main window in the GUI and is at the top of the window hierarchy.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/


#ifndef DGMAINWINDOW_H
#define DGMAINWINDOW_H

class DGMainWindow : public DGWindow
{
   DGMainWindow(UINT winID, bool control);
   DGMainWindow(UINT winID, bool control, DGRectangle dimensions);
   DGMainWindow(UINT winID, bool control, DGPoint position, DGPoint size);
   DGMainWindow(UINT winID, bool control, int xPos, int yPos,
      int width, int height);
   ~DGMainWindow();

   //Overridden Member Functions
   void SetPosition(DGPoint position);
   void SetPosition(int xPos, int yPos);

   void SetSize(DGPoint size);
   void SetSize(int width, int height);

   void SetDimensions(DGRectangle dimensions);
   void SetDimensions(DGPoint position, DGPoint size);
   void SetDimensions(int x, int y, int width, int height);

   void HideWindow(void);
   void ShowWindow(void);

   //Overridden Message Handlers
   void OnWindowReposition(int xPos, int yPos);
   void OnWindowResize(int width, int height);
};

#endif