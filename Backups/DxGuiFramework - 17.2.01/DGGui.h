/*------------------------------------------------------------------------
File Name: DGGui.h
Description: This file contains the DGGui class, which represents the
   Graphical User Interface of the application and manages windows and
   messages.
Version:
   1.0.0    10.02.2000  Created the file
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
   void ProcessMessages(void);

   DGWindow* GetWindow(UINT windowID);

   void SetWindowFocus(UINT windowID);
   UINT GetWindowFocus(void);
   void RemoveWindowFocus(void);

   void DrawGUI(void);

private:
   DGMainWindow* mainWindow;
   DGQueue<DGMessage> messageQueue;

   UINT focusedWindow;
};

#endif
