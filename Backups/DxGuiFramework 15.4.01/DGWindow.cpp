/*------------------------------------------------------------------------
File Name: DGWindow.cpp
Description: This file contains the implementations of the DGWindow class, 
	which represent a basic window in the GUI.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   UINT winID : the ID of the window to be constructed
   bool control : whether the window is a control or not
Description:
   This function constructs the DGWindow object.
------------------------------------------------------------------------*/

DGWindow::DGWindow(UINT winID, bool control)
{
   windowPosition.SetPoint(0, 0);
   windowSize.SetPoint(0, 0);

   windowID = winID;
   windowType = WT_GENERICWINDOW;
   isControl = control;

   windowShowing = false;

   parentWindow = NULL;

   windowList.SetDestroy(true);
   controlList.SetDestroy(true);
   hiddenWindowList.SetDestroy(true);

   HandleMessage(&DGMessage(GM_CREATE, windowID));
}

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   UINT winID : the ID of the window to be constructed
   bool control : whether the window is a control or not
   DGArea dimensions : the dimensions of the window to be constructed
Description:
   This function constructs the DGWindow object.
------------------------------------------------------------------------*/

DGWindow::DGWindow(UINT winID, bool control, const DGArea& dimensions)
{
   windowPosition.SetPoint(dimensions.left, dimensions.top);
   windowSize.SetPoint(dimensions.width, dimensions.height);

   windowID = winID;
   windowType = WT_GENERICWINDOW;
   isControl = control;

   windowShowing = true;

   parentWindow = NULL;

   windowList.SetDestroy(true);
   controlList.SetDestroy(true);
   hiddenWindowList.SetDestroy(true);

   HandleMessage(&DGMessage(GM_CREATE, windowID));
}

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   UINT winID : the ID of the window to be constructed
   bool control : whether the window is a control or not
   DGPoint position : the position of the window to be constructed
   DGPoint size : the size of the window to be constructed
Description:
   This function constructs the DGWindow object.
------------------------------------------------------------------------*/

DGWindow::DGWindow(UINT winID, bool control, const DGPoint& position, 
                   const DGPoint& size)
{
   windowPosition.SetPoint(position.x, position.y);
   windowSize.SetPoint(size.x, size.y);

   windowID = winID;
   windowType = WT_GENERICWINDOW;
   isControl = control;

   windowShowing = true;

   parentWindow = NULL;

   windowList.SetDestroy(true);
   controlList.SetDestroy(true);
   hiddenWindowList.SetDestroy(true);

   AddMessageHandler(GM_CREATE, (MsgHandlerFunction)this->OnCreate);
   HandleMessage(&DGMessage(GM_CREATE, windowID));
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
   This function constructs the DGWindow object.
------------------------------------------------------------------------*/

DGWindow::DGWindow(UINT winID, bool control, int xPos, int yPos,
                   int width, int height)
{
   windowPosition.SetPoint(xPos, yPos);
   windowSize.SetPoint(width, height);

   windowID = winID;
   windowType = WT_GENERICWINDOW;
   isControl = control;

   windowShowing = true;

   parentWindow = NULL;

   windowList.SetDestroy(true);
   controlList.SetDestroy(true);
   hiddenWindowList.SetDestroy(true);

   HandleMessage(&DGMessage(GM_CREATE, windowID));
}

/*Destructor*/
DGWindow::~DGWindow()
{
   HandleMessage(&DGMessage(GM_DESTROY, windowID));

   windowList.DeleteAll();
   controlList.DeleteAll();
   hiddenWindowList.DeleteAll();
}

/*------------------------------------------------------------------------
Function Name: SetPosition
Parameters:
   const DGPoint& position : a DGPoint object describing a new window
      position
Description:
   This function sets the window to a new position.
------------------------------------------------------------------------*/

void FC DGWindow::SetPosition(const DGPoint& position)
{
   windowPosition = position;
}

/*------------------------------------------------------------------------
Function Name: SetPosition
Parameters:
   int xPos : the x-coordinate of the new window position
   int yPos : the y-coordinate of the new window position
Description:
   This function sets the window to a new position.
------------------------------------------------------------------------*/

void FC DGWindow::SetPosition(int xPos, int yPos)
{
   windowPosition.SetPoint(xPos, yPos);
}  

/*------------------------------------------------------------------------
Function Name: SetSize
Parameters:
   const DGPoint& size : a DGPoint object describing a new window
      size
Description:
   This function resizes the window. It is assumed that the new width
   and height are greater than or equal to 0.
------------------------------------------------------------------------*/

void FC DGWindow::SetSize(const DGPoint& size)
{
   assert(size.y >= 0 && size.y >= 0);
   windowSize = size;
}

/*------------------------------------------------------------------------
Function Name: SetSize
Parameters:
   int width : the new width of the window
   int height : the new height of the window
Description:
   This function resizes the window. It is assumed that the new width
   and height are greater than or equal to 0.
------------------------------------------------------------------------*/

void FC DGWindow::SetSize(int width, int height)
{
   assert(width >= 0 && height >= 0);
   windowSize.SetPoint(width, height);
}

/*------------------------------------------------------------------------
Function Name: SetDimensions
Parameters:
   const DGArea& dimensions : a DGArea object describing a new window
      position and size
Description:
   This function sets the dimensions of the window. dimensions.left and
   dimensions.top describe the position of the window, dimensions.width
   and dimensions.height describe the width and height of the window.
   It is assumed that the specified width and height >= 0
------------------------------------------------------------------------*/

void FC DGWindow::SetDimensions(const DGArea& dimensions)
{
   assert(dimensions.width >= 0 && dimensions.height >= 0);
   windowPosition.SetPoint(dimensions.left, dimensions.top);
   windowSize.SetPoint(dimensions.width, dimensions.height);
}

/*------------------------------------------------------------------------
Function Name: SetDimensions
Parameters:
   const DGPoint& position : a DGPoint object describing a new window
      position
   const DGPoint& size : a DGPoint object describing a new window
      size
Description:
   This function sets the dimensions of the window. position describes
   the new position of the window, size.y and size.y describe the new 
   width and height of the window.
   It is assumed that the specified width and height >= 0
------------------------------------------------------------------------*/

void FC DGWindow::SetDimensions(const DGPoint& position, 
                                const DGPoint& size)
{
   assert(size.x >= 0 && size.y >= 0);
   windowPosition.SetPoint(position.x, position.y);
   windowSize.SetPoint(size.x, size.y);
}

/*------------------------------------------------------------------------
Function Name: SetDimensions
Parameters:
   int x : the x-coordinate of the new window position
   int y : the y-coordinate fo the new window position
   width : the new window width
   height : the new window height
Description:
   This function sets the dimensions of the window. 
   It is assumed that the specified width and height >= 0
------------------------------------------------------------------------*/

void FC DGWindow::SetDimensions(int x, int y, int width, int height)
{
   assert(width >= 0 && height >= 0);
   windowPosition.SetPoint(x, y);
   windowSize.SetPoint(width, height);
}

/*------------------------------------------------------------------------
Function Name: HideWindow
Parameters:
Description:
   This function hides the window by setting its windowShowing flag to
   false and telling its parent to put it in the hidden window list.
------------------------------------------------------------------------*/

void FC DGWindow::HideWindow()
{
   windowShowing = false;

   if(parentWindow != NULL)
   {
      DGGetGui()->PostMessage(new DGMessage(GM_HIDECHILDWINDOW, 
         parentWindow->GetWindowID(), 0, 0, windowID));
   }
}

/*------------------------------------------------------------------------
Function Name: HideWindow
Parameters:
Description:
   This function shows the window by setting its windowShowing flag to
   true and telling its parent to put it in the shown window list.
------------------------------------------------------------------------*/

void FC DGWindow::ShowWindow()
{
   windowShowing = true;

   if(parentWindow != NULL)
   {
      DGGetGui()->PostMessage(new DGMessage(GM_SHOWCHILDWINDOW, 
         parentWindow->GetWindowID(), 0, 0, windowID));
   }
}

//Child Window Functions

/*------------------------------------------------------------------------
Function Name: AddChildWindow
Parameters:
   DGWindow* childWindow : the child window to be added to this window
Description:
   This function receives a pointer to a window and makes it this 
   window's child by putting it in a child window list. The window
   will delete any child windows when it is destroyed.
------------------------------------------------------------------------*/

void FC DGWindow::AddChildWindow(DGWindow* childWindow)
{
   assert(childWindow != NULL);
   if(childWindow->IsWindowShowing())
   {
      if(childWindow->IsControl())
         controlList.Insert(childWindow, childWindow->GetWindowID());
      else
         windowList.Insert(childWindow, childWindow->GetWindowID());
   }
   else
   {
      hiddenWindowList.Insert(childWindow, childWindow->GetWindowID());
   }

   childWindow->SetParent(this);
}

/*------------------------------------------------------------------------
Function Name: GetWindow
Parameters:
   UINT windowID : the ID of a window
Description:
   This function receives a window ID and searches down the hierarchy
   for a window with that ID. If a window with the specified ID is found,
   a pointer to that window is returned. If no window with the specified
   ID is found, NULL is returned. There better not be any circular 
   dependencies in the window hierarchy otherwise this function will
   never finish.
------------------------------------------------------------------------*/

DGWindow* FC DGWindow::GetWindow(UINT winID)
{
   //If this window is the one we are looking for, return a pointer to it.
   if(windowID == winID)
      return this;

   else if(windowList.GetNumOfItems() == 0 && 
      controlList.GetNumOfItems() == 0 &&
      hiddenWindowList.GetNumOfItems() == 0)
      return NULL;

   else
   {
      DGWindow* winPtr = NULL;
      winPtr = windowList.GetItemById(winID);
      if(winPtr == NULL)
      {
         winPtr = controlList.GetItemById(winID);
         if(winPtr == NULL)
            winPtr = hiddenWindowList.GetItemById(winID);
      }

      return winPtr;
   }
}

/*------------------------------------------------------------------------
Function Name: DestroyWindow
Parameters:
   UINT windowID : the ID of a window
Description:
   This function receives a window ID and searches down the hierarchy
   for a window with that ID. If a window with the specified ID is found,
   it is deleted any references to it are removed from its parent window.
   The function returns true if the window was found and deleted and
   false if the window with the specified ID could not be found.
   There better not be any circular dependencies in the window hierarchy 
   otherwise this function will never finish.
------------------------------------------------------------------------*/

bool FC DGWindow::DestroyWindow(UINT winID)
{
   //If this window is the one we are looking for, tell its parent to
   //delete it
   if(windowID == winID)
   {
      if(parentWindow == NULL)
         delete this;
      else
         parentWindow->DestroyWindow(winID);

      return true;
   }

   else
   {
      bool found = false;
      DGWindow* window;

      window = windowList.RemoveById(winID);
      if(window != NULL)
      {
         delete window;
         found = true;
      }
      
      if(!found)
      {
         window = controlList.RemoveById(winID);
         if(window != NULL)
         {
            delete window;
            found = true;
         }

         if(!found)
         {
            window = hiddenWindowList.RemoveById(winID);
            if(window != NULL)
            {
               delete window;
               found = true;
            }
         }
      }

      return found;
   }
}

//Message Functions

/*------------------------------------------------------------------------
Function Name: SendMessage
Parameters:
   DGMessage* msg : a pointer to the message to be sent
Description:
   This function receives a pointer to a message that is to be sent.
   The message filters down through the window hierarchy so that it gets
   to its destination window. If the destination window is not within
   the hierarchy under this window, false is returned indicating that 
   the message did not reach its destination window. If the message did
   reach its destination window, true is returned.
------------------------------------------------------------------------*/

bool FC DGWindow::SendMessage(DGMessage* msg)
{
   //If this window is the intended recipient of the message, then handle
   //the message.
   if(windowID == msg->destination)
   {
      HandleMessage(msg);
      return true;
   }

   //If not, pass it down through the child windows
   else
   {
      bool windowFound = false;

      DGListIterator<DGWindow> iterator = windowList.Begin();
      while(!iterator.EndOfList() && !windowFound)
      {
         windowFound = iterator.GetData()->SendMessage(msg);
         iterator++;
      }

      iterator = controlList.Begin();
      while(!iterator.EndOfList() && !windowFound)
      {
         windowFound = iterator.GetData()->SendMessage(msg);
         iterator++;
      }

      iterator = hiddenWindowList.Begin();
      while(!iterator.EndOfList() && !windowFound)
      {
         windowFound = iterator.GetData()->SendMessage(msg);
         iterator++;
      }

      return windowFound;
   }
}

/*------------------------------------------------------------------------
Function Name: AddMessageHandler
Parameters:
   UINT messageType : a message type
   MsgHandlerFunction function : the function which will handle that
      type of message
Description:
   This function receives a message type and a function pointer and maps
   the message type to the function by storing the two parameters in
   the message table. Any further messages of the specified type received
   by this window will be handled by the specified function. If the 
   message type already exists in the table, this function will not do
   anything. The message handler entry must be removed before another
   message handler can be added for that message.
------------------------------------------------------------------------*/

void FC DGWindow::AddMessageHandler(UINT messageType, MsgHandlerFunction function)
{
   if(messageTable.count(messageType) == 0)
      messageTable.insert(MessageEntry(messageType, function));
}

/*------------------------------------------------------------------------
Function Name: RemoveMessageHandler
Parameters:
   UINT messageType : a message type
Description:
   This function receives a message type and removes any message handler
   associated with the message type from message table. If no message
   handler is associated with that message type when this function is
   called, nothing will happen.
------------------------------------------------------------------------*/

void FC DGWindow::RemoveMessageHandler(UINT messageType)
{
   messageTable.erase(messageType);
}

/*------------------------------------------------------------------------
Function Name: HandleMessage
Parameters:
   DGMessage msg : the message to be handled
Description:
   This function receives a pointer to a message to be handled and handles
   that message by calling the message handler associated with that 
   message type.
------------------------------------------------------------------------*/

void FC DGWindow::HandleMessage(DGMessage* msg)
{
   DGPoint point;

   switch(msg->messageType)
   {
      case GM_NONE:
         //We actually shouldn't be getting a message of this type
         break;
      case GM_FOCUS:
         OnSetFocus(msg->data3);
         break;
      case GM_LOSEFOCUS:
         OnLoseFocus(msg->data3);
         break;
      case GM_LBUTTONDOWN:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnLButtonDown(point.x, point.y, msg->keyboardState);
         break;
      case GM_LBUTTONUP:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnLButtonUp(point.x, point.y, msg->keyboardState);
         break;
      case GM_LBUTTONDBLCLK:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnLButtonDblClk(point.x, point.y, msg->keyboardState);
         break;
      case GM_MBUTTONDOWN:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnMButtonDown(point.x, point.y, msg->keyboardState);
         break;
      case GM_MBUTTONUP:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnMButtonUp(point.x, point.y, msg->keyboardState);
         break;
      case GM_MBUTTONDBLCLK:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnMButtonDblClk(point.x, point.y, msg->keyboardState);
         break;
      case GM_RBUTTONDOWN:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnRButtonDown(point.x, point.y, msg->keyboardState);
         break;
      case GM_RBUTTONUP:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnRButtonUp(point.x, point.y, msg->keyboardState);
         break;
      case GM_RBUTTONDBKCLK:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnRButtonDblClk(point.x, point.y, msg->keyboardState);
         break;
      case GM_MOUSEMOVE:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnMouseMove(point.x, point.y, msg->keyboardState);
         break;
      case GM_MOUSEENTER:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnMouseEnter(point.x, point.y, msg->keyboardState);
         break;
      case GM_MOUSELEAVE:
         point = AbsToRelCoords(msg->data1, msg->data2);
         OnMouseLeave(point.x, point.y, msg->keyboardState);
         break;
      case GM_KEYDOWN:
         OnKeyDown((BYTE)msg->data3, msg->keyboardState);
         break;
      case GM_KEYUP:
         OnKeyDown((BYTE)msg->data3, msg->keyboardState);
         break;
      case GM_MOVING:
         OnWindowMoving();
         break;
      case GM_MOVED:
         OnWindowMoved();
         break;
      case GM_REPOSITION:
         OnWindowReposition(msg->data1, msg->data2);
         break;
      case GM_SIZING:
         OnWindowSizing();
         break;
      case GM_SIZED:
         OnWindowSized();
         break;
      case GM_RESIZE:
         OnWindowResize(msg->data1, msg->data2);
         break;
      case GM_SHOWWINDOW:
         OnShowWindow();
         break;
      case GM_HIDEWINDOW:
         OnHideWindow();
         break;
      case GM_DISPLAYCHANGE:
      {
         DGResolutionMessage* resMsg = (DGResolutionMessage*)msg;
         OnDisplayChange(resMsg->newXResPercentage, resMsg->newYResPercentage,
            resMsg->data3);
         break;
      }
      case GM_CREATE:
         OnCreate();
         break;
      case GM_DESTROY:
         OnDestroy();
         break;
      case GM_HIDECHILDWINDOW:
         OnShowChildWindow(msg->data3);
         break;
      case GM_SHOWCHILDWINDOW:
         OnHideChildWindow(msg->data3);
         break;
      default:
         //If the message was not a basic framework message, then look
         //for it in the message table
         MessageTable::iterator it = messageTable.find(msg->messageType);
         if(it != messageTable.end())
         {
            MsgHandlerFunction function = (*it).second;
            (this->*function)(msg);
         }
   }
}

//Default Message Handlers

/*------------------------------------------------------------------------
Function Name: OnSetFocus
Parameters:
   winID : the ID of the window that lost the focus
Description:
   This function is called when a GM_FOCUS message is received, meaning
   that the window has gained the focus.
------------------------------------------------------------------------*/

void FC DGWindow::OnSetFocus(UINT winID)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnLoseFocus
Parameters:
   winID : the ID of the window that gained the focus
Description:
   This function is called when a GM_LOSEFOCUS message is received, meaning
   that the window has lost the focus.
------------------------------------------------------------------------*/

void FC DGWindow::OnLoseFocus(UINT winID)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnLButtonDown
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_LBUTTONDOWN message is received, 
   meaning that the left mouse button was pushed down within the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnLButtonUp
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_LBUTTONUP message is received, 
   meaning that the left mouse button was released within the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnLButtonDblClk
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_LBUTTONDBLCLK message is received, 
   meaning that the left mouse button was double clicked within 
   the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnLButtonDblClk(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnMButtonDown
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_MBUTTONDOWN message is received, 
   meaning that the middle mouse button was pushed down within 
   the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnMButtonDown(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnMButtonUp
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_MBUTTONUP message is received, 
   meaning that the middle mouse button was released within the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnMButtonUp(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnMButtonDblClk
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_MBUTTONDBLCLK message is received, 
   meaning that the middle mouse button was double clicked within 
   the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnMButtonDblClk(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnRButtonDown
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_RBUTTONDOWN message is received, 
   meaning that the right mouse button was pushed down within the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnRButtonDown(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnRButtonUp
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_RBUTTONUP message is received, 
   meaning that the right mouse button was released within the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnRButtonUp(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnRButtonDblClk
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_RBUTTONDBLCLK message is received, 
   meaning that the right mouse button was double clicked within 
   the window.
------------------------------------------------------------------------*/

void FC DGWindow::OnRButtonDblClk(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnMouseMove
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_MOUSEMOVE message is received, 
   meaning that the mouse cursor was moved withing the window
------------------------------------------------------------------------*/

void FC DGWindow::OnMouseMove(int x, int y, BYTE* keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnMouseEnter
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_MOUSEENTER message is received, 
   meaning that the mouse cursor has entered the window
------------------------------------------------------------------------*/

void FC DGWindow::OnMouseEnter(int x, int y, BYTE* keyboardState)
{
   //Do Nothing
}

/*------------------------------------------------------------------------
Function Name: OnMouseLeave
Parameters:
   int x - the relative x-coordinate of the mouse cursor
   int y - the relative y-coordinate of the mouse cursor
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_MOUSELEAVE message is received, 
   meaning that the mouse cursor has left the window
------------------------------------------------------------------------*/

void FC DGWindow::OnMouseLeave(int x, int y, BYTE* keyboardState)
{
   //Do Nothing
}

/*------------------------------------------------------------------------
Function Name: OnKeyDown
Parameters:
   BYTE keyCode - the virtual key code corresponding to the key being
      pressed.
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_KEYDOWN message is received, 
   meaning that a key has been pressed when the window has the focus.
------------------------------------------------------------------------*/

void FC DGWindow::OnKeyDown(BYTE keyCode, PBYTE keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnKeyPressed
Parameters:
   BYTE keyCode - the virtual key code corresponding to the key being
      released.
   BYTE* keyboardState - a pointer to a 256-byte array describing the
      state of the keys and the mouse buttons
Description:
   This function is called when a GM_KEYUP or a GM_KEYPRESSED message 
   is received, meaning that a key has been released when the window 
   has the focus. Often when wanting to know if a key has been pressed,
   it is useful to do something just after it is released.
------------------------------------------------------------------------*/

void FC DGWindow::OnKeyPressed(BYTE keyCode, PBYTE keyboardState)
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnWindowMoving
Parameters:
Description:
   This function is called when a GM_MOVING message is received, 
   meaning that the window is currently being moved. This message is not
   generated automatically by the framework, but has to be sent by a 
   control.
------------------------------------------------------------------------*/

void FC DGWindow::OnWindowMoving()
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnWindowMoved
Parameters:
Description:
   This function is called when a GM_MOVED message is received, 
   meaning that the window has been moved and that the moving operation
   has been completed. This message is not generated automatically by 
   the framework, but has to be sent by a control.
------------------------------------------------------------------------*/

void FC DGWindow::OnWindowMoved()
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnWindowReposition
Parameters:
   int xPos - the x-coordinate of the new window position
   int yPos - the y-coordinate of the new window position
Description:
   This function is called when a GM_REPOSITION message is received, 
   meaning that the window is being commanded to move to the specified
   coordinates. This message is not generated automatically by 
   the framework, but has to be sent by a control.
------------------------------------------------------------------------*/

void FC DGWindow::OnWindowReposition(int xPos, int yPos)
{
   SetPosition(xPos, yPos);
}

/*------------------------------------------------------------------------
Function Name: OnWindowSizing
Parameters:
Description:
   This function is called when a GM_SIZING message is received, 
   meaning that the window is currently being resized. This message is 
   not generated automatically by the framework, but has to be sent by a 
   control.
------------------------------------------------------------------------*/

void FC DGWindow::OnWindowSizing()
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnWindowSized
Parameters:
Description:
   This function is called when a GM_SIZED message is received, 
   meaning that the window has been resized and that the resizing 
   operation has been completed. This message is not generated 
   automatically by the framework, but has to be sent by a control.
------------------------------------------------------------------------*/

void FC DGWindow::OnWindowSized()
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnWindowResize
Parameters:
   int xPos - the new width of the window
   int yPos - the new height of the window
Description:
   This function is called when a GM_RESIZE message is received, 
   meaning that the window is being commanded to resize to the specified
   width and height. This message is not generated automatically by 
   the framework, but has to be sent by a control.
------------------------------------------------------------------------*/

void FC DGWindow::OnWindowResize(int width, int height)
{
   SetSize(width, height);
}

/*------------------------------------------------------------------------
Function Name: OnShowWindow
Parameters:
Description:
   This function is called when a GM_SHOWWINDOW message is received, 
   meaning that the window is being commanded to show itself.
------------------------------------------------------------------------*/

void FC DGWindow::OnShowWindow()
{
   ShowWindow();
}

/*------------------------------------------------------------------------
Function Name: OnShowWindow
Parameters:
Description:
   This function is called when a GM_HIDEWINDOW message is received, 
   meaning that the window is being commanded to hide itself.
------------------------------------------------------------------------*/

void FC DGWindow::OnHideWindow()
{
   HideWindow();
}

/*------------------------------------------------------------------------
Function Name: OnDisplayChange
Parameters:
   float xRelChange - the percentage of the resolution width change 
   float yRelChange - the percentage of the resolution height change
   UINT colorDepth - the color depth of the new graphics mode
Description:
   This function is called when a GM_DISPLAYCHANGE message is received, 
   meaning that the resolution and/or color depth has change. The default
   behavior of this function is to change to size and positon of the 
   window so that it matches the resolution change.
------------------------------------------------------------------------*/

void FC DGWindow::OnDisplayChange(float xRelChange, float yRelChange,
                                  UINT colorDepth)
{
   SetPosition(windowPosition.x * xRelChange, 
      windowPosition.y * yRelChange);
   SetSize(windowSize.x * xRelChange, 
      windowSize.y * yRelChange);
}

/*------------------------------------------------------------------------
Function Name: OnCreate
Parameters:
Description:
   This function is called when a GM_CREATE message is received, 
   meaning that the window is being created. At this point the 
   constructor has already been called.
------------------------------------------------------------------------*/

void DGWindow::OnCreate()
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnDestroy
Parameters:
Description:
   This function is called when a GM_DESTROY message is received, 
   meaning that the window is being destroyed. At this point, the
   destructor has not been called yet.
------------------------------------------------------------------------*/

void FC DGWindow::OnDestroy()
{
   //Do nothing
}

/*------------------------------------------------------------------------
Function Name: OnShowChildWindow
Parameters:
Description:
   This function is called when a GM_SHOWCHILDWINDOW message is received, 
   meaning that the window should show one of its child windows. This is
   necessary in the showing of windows, as they rely on which window list
   they are in.
------------------------------------------------------------------------*/

void FC DGWindow::OnShowChildWindow(UINT winID)
{
   //We only need to look in hidden window list
   DGWindow* window = hiddenWindowList.GetItemById(winID);

   if(window != NULL)
   {
      hiddenWindowList.RemoveById(winID);
      if(window->IsControl())
         controlList.Insert(window);
      else
         windowList.Insert(window);
   }
}

/*------------------------------------------------------------------------
Function Name: OnHideChildWindow
Parameters:
Description:
   This function is called when a GM_HIDECHILDWINDOW message is received, 
   meaning that the window should hide one of its child windows. This is
   necessary in the hiding of windows, as they rely on which window list
   they are in.
------------------------------------------------------------------------*/

void FC DGWindow::OnHideChildWindow(UINT winID)
{
   //We only need to look in the control and shown window lists
   DGWindow* window = windowList.RemoveById(winID);

   if(window != NULL)
      hiddenWindowList.Insert(window);

   else
   {
      DGWindow* window = controlList.RemoveById(winID);

      if(window != NULL)
         hiddenWindowList.Insert(window);
   }
}

//Window Coordinate Functions

/*------------------------------------------------------------------------
Function Name: AreCoordsInWindow
Parameters:
   DGMainWindow mainWin : a pair of absolute coordinates
Description:
   This function receives a pair of absolute coordinates and returns
   true if those coordinates are within the window, false otherwise.
------------------------------------------------------------------------*/

bool FC DGWindow::AreCoordsInWindow(int x, int y)
{
   if(x >= windowPosition.x && x < windowPosition.x + windowSize.x &&
      y >= windowPosition.y && y < windowPosition.y + windowSize.y)
      return true;
   else
      return false;
}

/*------------------------------------------------------------------------
Function Name: GetWinIDOfCoords
Parameters:
   int x : the x-value of a pair of absolute coordinates
   int y : the y-value of a pair of absolute coordinates
Description:
   This function receives a pair of absolute coordinates and returns the
   ID of the topmost window that contains that point on the screen.
   If no window in the window hierarchy contains that point, IDW_NONE is
   returned.
------------------------------------------------------------------------*/

UINT FC DGWindow::GetWinIDOfCoords(int x, int y)
{
   if(!AreCoordsInWindow(x, y))
      return IDW_NONE;

   UINT winID = IDW_NONE;
   DGWindow* window = NULL;

   //Loop through the shown windows
   DGListIterator<DGWindow> iterator = windowList.Begin();
   while(winID == IDW_NONE && !iterator.EndOfList())
   {
      window = iterator.GetData();
      winID = window->GetWinIDOfCoords(x, y);
      iterator++;
   }

   //If we've found it, return it
   if(winID != IDW_NONE)
      return winID;

   //Loop through the controls
   iterator = controlList.Begin();
   while(winID == IDW_NONE && !iterator.EndOfList())
   {
      window = iterator.GetData();
      winID = window->GetWinIDOfCoords(x, y);
      iterator++;
   }

   return winID;
}

/*------------------------------------------------------------------------
Function Name: GetWinIDOfCoords
Parameters:
   int x : the x-value of a pair of absolute coordinates
   int y : the y-value of a pair of absolute coordinates
Description:
   This function receives a pair of absolute coordinates and returns a
   pair of coordinates relative to the upper-left corner of the window.
------------------------------------------------------------------------*/

DGPoint FC DGWindow::AbsToRelCoords(int x, int y)
{
   return DGPoint(x - windowPosition.x, y - windowPosition.y);
}

/*------------------------------------------------------------------------
Function Name: GetWinIDOfCoords
Parameters:
   int x : the x-value of a pair of relative coordinates
   int y : the y-value of a pair of relative coordinates
Description:
   This function receives a pair of coordinates relative to the 
   upper-left corner of the window and returns a
   pair of absolute coordinates.
------------------------------------------------------------------------*/

DGPoint FC DGWindow::RelToAbsCoords(int x, int y)
{
   return DGPoint(x + windowPosition.x, y + windowPosition.y);
}
