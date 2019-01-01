/*------------------------------------------------------------------------
File Name: DGGui.h
Description: This file contains the DGGui class, which represents the
   Graphical User Interface of the application and manages windows and
   messages.
Version:
   1.0.0    10.02.2001  Created the file
------------------------------------------------------------------------*/


#ifndef DGGUI_H
#define DGGUI_H

class DGGui
{
public:
   DGGui();
   virtual ~DGGui();

   void SetMainWindow(DGMainWindow* mainWin);
   DGMainWindow* GetMainWindow(void) {return mainWindow;}

   void PostMessage(DGMessage* msg);
   void SendMessage(DGMessage* msg);
   void GenerateMessages(void);
   void DispatchMessages(void);

   DGWindow* GetWindow(UINT windowID);

   void SetWindowFocus(UINT windowID);
   UINT GetWindowFocus(void);
   void RemoveWindowFocus(void);

   void SetMouseCapture(UINT windowID);
   void ReleaseMouseCapture(void);
   UINT GetMouseCapture(void);

   void DrawGUI(void);

private:
   DGMainWindow* mainWindow;
   DGQueue<DGMessage> messageQueue;

   UINT focusedWindow;

   //The window that has the mouse capture (always gets mouse messages)
   UINT mouseCaptureWinID;

   //The ID of the window the mouse cursor was previously in
   UINT prevMouseCursorWinID;

   //Stores where the mouse cursor was the last time a GM_MOUSEMOVE
   //message was generated, this is needed for the GM_MOUSELEAVE message
   int prevXPos;
   int prevYPos;

#ifdef DGMESSAGELOG
   DGMessageLog messageLog;
#endif
};

#endif
