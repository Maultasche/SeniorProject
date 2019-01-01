/*------------------------------------------------------------------------
File Name: DGWindow.h
Description: This file contains the DGWindow class, which represent a
   basic window in the GUI.
Version:
   1.0.0    10.02.2001  Created the file
------------------------------------------------------------------------*/


#ifndef WINDOW_H
#define WINDOW_H

class DGWindow
{
public:
   DGWindow(UINT winID, bool control);
   DGWindow(UINT winID, bool control, const DGArea& dimensions);
   DGWindow(UINT winID, bool control, const DGPoint& position, 
      const DGPoint& size);
   DGWindow(UINT winID, bool control, int xPos, int yPos,
      int width, int height);
   virtual ~DGWindow();

   virtual void FC SetPosition(const DGPoint& position);
   virtual void FC SetPosition(int xPos, int yPos);
   DGPoint GetPosition(void) {return windowPosition;}

   virtual void FC SetSize(const DGPoint& size);
   virtual void FC SetSize(int width, int height);
   DGPoint GetSize(void) {return windowSize;}

   virtual void FC SetDimensions(const DGArea& dimensions);
   virtual void FC SetDimensions(const DGPoint& position, 
      const DGPoint& size);
   virtual void FC SetDimensions(int x, int y, int width, int height);
   DGArea GetDimensions(void) 
   {return DGArea(windowPosition, windowSize);}
   DGArea GetAbsDimensions(void)
   {return DGArea(absWindowPosition, windowSize);}

   DGPoint GetAbsPosition(void) {return absWindowPosition;}

   virtual void FC HideWindow(void);
   virtual void FC ShowWindow(void);

   virtual void FC DrawWindow(void);

   bool IsWindowShowing(void) {return windowShowing;}
   bool IsControl(void) {return isControl;}

   UINT GetWindowID(void) {return windowID;}
   UINT GetWindowType(void) {return windowType;}

   void SetParent(DGWindow* window) 
   {
      parentWindow = window;
      CalculateAbsCoords();
   }

   DGWindow* GetParent(void) {return parentWindow;}

   //Child Window Functions
   virtual void FC AddChildWindow(DGWindow* childWindow);
   virtual DGWindow* FC GetWindow(UINT winID);
   virtual bool FC DestroyWindow(UINT winID);
   virtual void FC SetChildWindowDraw(bool draw) {drawChildWindows = draw;}
   virtual bool FC GetChildWindowDraw(void) {return drawChildWindows;}
   virtual void FC SetParentClipping(bool clipping) {parentClipping = clipping;}
   virtual bool FC GetParentClipping(void) {return parentClipping;}

   //Message Functions
   virtual bool FC SendMessage(DGMessage* msg);
   virtual bool FC SendChildMessage(DGMessage* msg);
   virtual void FC BroadcastMessage(DGMessage* msg);
   virtual void FC AddMessageHandler(UINT messageID, 
      MsgHandlerInterface* function);
   virtual void FC RemoveMessageHandler(UINT messageID);
   virtual void FC HandleMessage(DGMessage* msg);

   //Window Coordinate Functions
   bool FC AreCoordsInWindow(int x, int y);
   UINT FC GetWinIDOfCoords(int x, int y);
   UINT FC GetChildWinIDOfCoords(int x, int y);
   DGPoint FC AbsToRelCoords(int x, int y);
   DGPoint FC RelToAbsCoords(int x, int y);

   //Calls OnCreate or OnDestroy
   virtual void FC Create(void);
   virtual void FC Destroy(void);

protected:
   void SetWindowType(UINT type) {windowType = type;}

   //Default Message Handlers
   virtual void FC OnSetFocus(UINT winID);
   virtual void FC OnLoseFocus(UINT winID);
   virtual void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   virtual void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   virtual void FC OnLButtonDblClk(int x, int y, BYTE* keyboardState);
   virtual void FC OnMButtonDown(int x, int y, BYTE* keyboardState);
   virtual void FC OnMButtonUp(int x, int y, BYTE* keyboardState);
   virtual void FC OnMButtonDblClk(int x, int y, BYTE* keyboardState);
   virtual void FC OnRButtonDown(int x, int y, BYTE* keyboardState);
   virtual void FC OnRButtonUp(int x, int y, BYTE* keyboardState);
   virtual void FC OnRButtonDblClk(int x, int y, BYTE* keyboardState);
   virtual void FC OnMouseMove(int x, int y, BYTE* keyboardState);
   virtual void FC OnMouseEnter(int x, int y, BYTE* keyboardState);
   virtual void FC OnMouseLeave(int x, int y, BYTE* keyboardState);
   virtual void FC OnKeyDown(BYTE keyCode, PBYTE keyboardState);
   virtual void FC OnKeyPressed(BYTE keyCode, PBYTE keyboardState);
   virtual void FC OnCharacter(char character, PBYTE keyboardState);
   virtual void FC OnWindowMoving(void);
   virtual void FC OnWindowMoved(void);
   virtual void FC OnWindowReposition(int xPos, int yPos);
   virtual void FC OnWindowSizing(void);
   virtual void FC OnWindowSized(void);
   virtual void FC OnWindowResize(int width, int height);
   virtual void FC OnShowWindow(void);
   virtual void FC OnHideWindow(void);
   virtual void FC OnDisplayChange(float xRelChange, float yRelChange,
      UINT colorDepth);
   virtual void FC OnCreate(void);
   virtual void FC OnDestroy(void);
   virtual void FC OnShowChildWindow(UINT winID);
   virtual void FC OnHideChildWindow(UINT winID);
   virtual void FC OnParentReposition(void);
   virtual void FC OnDrawWindow(DGWindowSurface* surface);

private:
   void CalculateAbsCoords(void);

   DGPoint windowPosition;
   DGPoint windowSize;

   DGPoint absWindowPosition;

   UINT windowID;
   UINT windowType;

   bool windowShowing;
   bool isControl;

   DGWindow* parentWindow;

   //The message handler table
   MessageTable messageTable;

   //Z-ordered child window lists
   DGLinkedList<DGWindow> windowList;
   DGLinkedList<DGWindow> controlList;
   DGLinkedList<DGWindow> hiddenWindowList;

   bool isCreated;
   bool isDestroyed;
   bool drawChildWindows;
   bool parentClipping;
};

#endif