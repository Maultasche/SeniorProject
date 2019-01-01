/*------------------------------------------------------------------------
File Name: DGWindow.h
Description: This file contains the DGWindow class, which represent a
   basic window in the GUI.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/


#ifndef WINDOW_H
#define WINDOW_H

class DGWindow
{
public:
   DGWindow(UINT winID, bool control);
   DGWindow(UINT winID, bool control, DGRectangle dimensions);
   DGWindow(UINT winID, bool control, DGPoint position, DGPoint size);
   DGWindow(UINT winID, bool control, int xPos, int yPos,
      int width, int height);
   virtual ~DGWindow();

   virtual void SetPosition(DGPoint position);
   virtual void SetPosition(int xPos, int yPos);
   DGPoint GetPosition(void) {return windowPosition;}

   virtual void SetSize(DGPoint size);
   virtual void SetSize(int width, int height);
   DGPoint GetSize(void) {return windowSize;}

   virtual void SetDimensions(DGRectangle dimensions);
   virtual void SetDimensions(DGPoint position, DGPoint size);
   virtual void SetDimensions(int x, int y, int width, int height);
   DGRectangle GetDimensions(void) 
   {return DGRectangle(windowPosition, windowSize);}

   virtual void HideWindow(void);
   virtual void ShowWindow(void);

   bool IsWindowShowing(void) {return windowShowing;}

   UINT GetWindowID(void) {return windowID;}

   DGWindow* GetParent(void) {return parentWindow;}

   //Child Window Functions
   virtual void AddChildWindow(DGWindow* childWindow);
   virtual DGWindow* GetWindow(UINT windowID);
   virtual void DestroyWindow(UINT windowID);

   //Message Functions
   virtual bool SendMessage(DGMessage* msg);
   virtual void AddMessageHandler(UINT messageID, MsgHandlerFunction function);
   virtual void RemoveMessageHandler(UINT messageID);

   //Default Message Handlers
   virtual void OnSetFocus(void);
   virtual void OnLoseFocus(void);
   virtual void OnLButtonDown(int x, int y);
   virtual void OnLButtonUp(int x, int y);
   virtual void OnMButtonDown(int x, int y);
   virtual void OnMButtonUp(int x, int y);
   virtual void OnRButtonDown(int x, int y);
   virtual void OnRButtonUp(int x, int y);
   virtual void OnMouseEnter(int x, int y);
   virtual void OnMouseLeave(int x, int y);
   virtual void OnKeyDown(BYTE keyCode, PBYTE keyboardState);
   virtual void OnKeyPressed(BYTE keyCode, PBYTE keyboardState);
   virtual void OnWindowMoving(void);
   virtual void OnWindowMoved(void);
   virtual void OnWindowReposition(int xPos, int yPos);
   virtual void OnWindowSizing(void);
   virtual void OnWindowSized(void);
   virtual void OnWindowResize(int width, int height);
   virtual void OnShowWindow(void);
   virtual void OnHideWindow(void);
   virtual void OnDisplayChange(float xRelChange, float yRelChange);
   virtual void OnCreate(void);
   virtual void OnDestroy(void);

   //Window Coordinate Functions
   bool AreCoordsInWindow(int x, int y);
   UINT GetWinIDOfCoords(int x, int y);
   DGPoint AbsToRelCoords(int x, int y);
   DGPoint RelToAbsCoords(int x, int y);

private:
   DGPoint windowPosition;
   DGPoint windowSize;

   UINT windowID;
   UINT windowType;

   bool windowShowing;

   DGWindow* parentWindow;

   //Add Message-Handler Table here

   //Z-ordered child window lists
   DGLinkedList<DGWindow> windowList;
   DGLinkedList<DGWindow> controlList;
   DGLinkedList<DGWindow> hiddenWindowList;

};

#endif