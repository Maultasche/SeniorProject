/*------------------------------------------------------------------------
File Name: DGGui.cpp
Description: This file contains the implementation of theDGGui class, 
   which represents the graphical user interface of the application 
   and manages windows and messages.
Version:
   1.0.0    10.02.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
Description:
   This function constructs the DGGui object and creates a default main
   window.
------------------------------------------------------------------------*/

DGGui::DGGui()
{
   //The main window can't be constructed here; when the application is
   //created, the DGGraphics object hasn't been created yet, so there
   //is no way to know the resolution of the screen
   mainWindow = NULL;
   mouseCaptureWinID = IDW_NONE;
   prevMouseCursorWinID = IDW_NONE;
}

/*Destructor*/
DGGui::~DGGui()
{
   //Destroy the main window, which will cause it do destroy all its
   //child windows.
   if(mainWindow != NULL)
      delete mainWindow;
}

/*------------------------------------------------------------------------
Function Name: SetMainWindow
Parameters:
   DGMainWindow mainWin : the pointer to the window to be made the main
      window
Description:
   This function receives a pointer to a window to be the main window
   and makes it the main window. If the window will be resized as
   necessary so that it covers the entire screen. The new main window
   will automatically be given the focuse. The previous main window will 
   be deleted. The pointer to the main window is assumed to be a valid 
   pointer.
------------------------------------------------------------------------*/

void DGGui::SetMainWindow(DGMainWindow* mainWin)
{
   assert(mainWin != NULL);

   DGPoint screenRes = dgGraphics->GetResolution();
   mainWin->SetDimensions(DGPoint(0, 0), screenRes);
   
   //Make sure the old window is destroyed
   if(mainWindow != NULL)
   {
      mainWindow->Destroy();
      delete mainWindow;
   }

   mainWindow = mainWin;

   //Make sure the new window is created
   mainWindow->Create();

   SetWindowFocus(mainWindow->GetWindowID());
}

/*------------------------------------------------------------------------
Function Name: PostMessage
Parameters:
   DGMessage msg : a pointer to the message to be put on the message
      queue.
Description:
   This function receives a pointer a message to be put on the message
   queue and puts that message at the end of the message queuek. 
   The pointer to the message is assumed to be a valid pointer.
------------------------------------------------------------------------*/

void DGGui::PostMessage(DGMessage* msg)
{
   assert(msg != NULL);

   messageQueue.Enqueue(msg, msg->messageType);
}

/*------------------------------------------------------------------------
Function Name: SendMessage
Parameters:
   DGMessage msg : a pointer to the message to be sent
Description:
   This function receives a pointer a message and immediately sends that
   message. This function behaves asynchronously and does not wait until
   the usual message-dispatching phase to send the message. This
   function deletes the message when it is done with it.
------------------------------------------------------------------------*/

void DGGui::SendMessage(DGMessage* msg)
{
   assert(msg != NULL);

   mainWindow->SendMessage(msg);

   delete msg;
}

/*------------------------------------------------------------------------
Function Name: GenerateMessages
Parameters:
Description:
   This function generates GUI messages based on user input, such as key
   presses and mouse movement.
------------------------------------------------------------------------*/

void DGGui::GenerateMessages(void)
{
   InputEvent* event = NULL;
   DGMessage* message = NULL;
   int xPos = 0;
   int yPos = 0;
   UINT windowID = IDW_NONE;

   //Loop throught the input event queue and generate messages from
   //each input event.
   while(dgInput->EventsInQueue())
   {
      event = dgInput->RemoveEvent();
     
      switch(event->messageType)
      {
         case WM_KEYDOWN:
         case WM_SYSKEYDOWN:
            message = new DGMessage(GM_KEYDOWN, focusedWindow, 0, 0,
               event->wParam, event->keyboardState);
            PostMessage(message);
            break;
         case WM_KEYUP:
         case WM_SYSKEYUP:
            message = new DGMessage(GM_KEYUP, focusedWindow, 0, 0,
               event->wParam, event->keyboardState);
            PostMessage(message);
            break;
         case WM_CHAR:
            if(focusedWindow != IDW_NONE)
            {
               message = new DGMessage(GM_CHARACTER, focusedWindow, 0, 0, 
                  LOBYTE(LOWORD(event->wParam)), event->keyboardState);
               PostMessage(message);
            }
            break;
         case WM_LBUTTONDOWN:
            //Get the absolute x and y coordinates
            xPos = LOWORD(event->lParam);
            yPos = HIWORD(event->lParam);

            //If the mouse is captured, send it to that window
            if(mouseCaptureWinID != IDW_NONE)
               windowID = mouseCaptureWinID;
            //Otherwise find the window at those coordinates
            else
               windowID = mainWindow->GetWinIDOfCoords(xPos, yPos);

            //Put the message on the queue
            message = new DGMessage(GM_LBUTTONDOWN, windowID, xPos, yPos, 0, 
               event->keyboardState);
            PostMessage(message);
            break;
         case WM_LBUTTONUP:
            //Get the absolute x and y coordinates
            xPos = LOWORD(event->lParam);
            yPos = HIWORD(event->lParam);

            //If the mouse is captured, send it to that window
            if(mouseCaptureWinID != IDW_NONE)
               windowID = mouseCaptureWinID;
            //Otherwise find the window at those coordinates
            else
               windowID = mainWindow->GetWinIDOfCoords(xPos, yPos);

            //Put the message on the queue
            message = new DGMessage(GM_LBUTTONUP, windowID, xPos, yPos, 0, 
               event->keyboardState);
            PostMessage(message);
            break;
         case WM_MBUTTONDOWN:
            //Get the absolute x and y coordinates
            xPos = LOWORD(event->lParam);
            yPos = HIWORD(event->lParam);

            //If the mouse is captured, send it to that window
            if(mouseCaptureWinID != IDW_NONE)
               windowID = mouseCaptureWinID;
            //Otherwise find the window at those coordinates
            else
               windowID = mainWindow->GetWinIDOfCoords(xPos, yPos);

            //Put the message on the queue
            message = new DGMessage(GM_MBUTTONDOWN, windowID, xPos, yPos, 0, 
               event->keyboardState);
            PostMessage(message);
            break;
         case WM_MBUTTONUP:
            //Get the absolute x and y coordinates
            xPos = LOWORD(event->lParam);
            yPos = HIWORD(event->lParam);

            //If the mouse is captured, send it to that window
            if(mouseCaptureWinID != IDW_NONE)
               windowID = mouseCaptureWinID;
            //Otherwise find the window at those coordinates
            else
               windowID = mainWindow->GetWinIDOfCoords(xPos, yPos);

            //Put the message on the queue
            message = new DGMessage(GM_MBUTTONUP, windowID, xPos, yPos, 0, 
               event->keyboardState);
            PostMessage(message);
            break;
         case WM_RBUTTONDOWN:
            //Get the absolute x and y coordinates
            xPos = LOWORD(event->lParam);
            yPos = HIWORD(event->lParam);

            //If the mouse is captured, send it to that window
            if(mouseCaptureWinID != IDW_NONE)
               windowID = mouseCaptureWinID;
            //Otherwise find the window at those coordinates
            else
               windowID = mainWindow->GetWinIDOfCoords(xPos, yPos);

            //Put the message on the queue
            message = new DGMessage(GM_RBUTTONDOWN, windowID, xPos, yPos, 0, 
               event->keyboardState);
            PostMessage(message);
            break;
         case WM_RBUTTONUP:
            //Get the absolute x and y coordinates
            xPos = LOWORD(event->lParam);
            yPos = HIWORD(event->lParam);

            //If the mouse is captured, send it to that window
            if(mouseCaptureWinID != IDW_NONE)
               windowID = mouseCaptureWinID;
            //Otherwise find the window at those coordinates
            else
               windowID = mainWindow->GetWinIDOfCoords(xPos, yPos);

            //Put the message on the queue
            message = new DGMessage(GM_RBUTTONUP, windowID, xPos, yPos, 0, 
               event->keyboardState);
            PostMessage(message);
            break;
         case WM_MOUSEMOVE:
            
            //Get the absolute x and y coordinates
            xPos = LOWORD(event->lParam);
            yPos = HIWORD(event->lParam);

            //If the mouse is captured, send it to that window
            if(mouseCaptureWinID != IDW_NONE)
               windowID = mouseCaptureWinID;
            //Otherwise find the window at those coordinates
            else
               windowID = mainWindow->GetWinIDOfCoords(xPos, yPos);

            //If necessary, generate GM_MOUSEENTER and GM_MOUSELEAVE 
            //messages
            if(windowID != prevMouseCursorWinID)
            {
               message = new DGMessage(GM_MOUSELEAVE, prevMouseCursorWinID, 
                  prevXPos, prevYPos);
               PostMessage(message);
               message = new DGMessage(GM_MOUSEENTER, windowID, xPos, yPos);
               PostMessage(message);
               prevMouseCursorWinID = windowID;
            }

            //Generate the GM_MOUSEMOVE message
            //Put the GM_MOUSEMOVE message on the queue
            message = new DGMessage(GM_MOUSEMOVE, windowID, xPos, yPos);
            PostMessage(message);

            //Save where the mouse cursor was in case a GM_MOUSELEAVE message
            //needs to be generated next time
            prevXPos = xPos;
            prevYPos = yPos;
            break;
         case WM_TIMER:
            UINT timerID = event->wParam;
            std::map<UINT, UINT>::iterator it = timerTable.find(timerID);

            //If we can find an entry for this timer, then send the message
            if(it != timerTable.end())
            {
               UINT windowID = (*it).second;
               message = new DGMessage(GM_TIMER, windowID, 0, 0, timerID);
               PostMessage(message);
            }

            //If we cannot find an entry for this timer, then destroy it
            else
               DestroyTimer(timerID);

            break;
      }
   }
}

/*------------------------------------------------------------------------
Function Name: DispatchMessages
Parameters:
Description:
   This function dispatches all the messages in the message queue until
   it becomes empty. The messages are removed from the message queue
   and sent to the window hierarchy.
------------------------------------------------------------------------*/

void DGGui::DispatchMessages(void)
{
   DGMessage* message = NULL;

   while(messageQueue.GetNumOfItems() > 0)
   {
      //Remove the next message from the message queue
      message = messageQueue.Dequeue();

#ifdef DGMESSAGELOG
      messageLog.LogMessage(message);
#endif

      mainWindow->SendMessage(message);

      //Destroy the message after it has been dispatched and handled
      delete message;
   }
}

/*------------------------------------------------------------------------
Function Name: GetWindow
Parameters:
   UINT windowID : the ID of a window 
Description:
   This function receives a window ID and returns a pointer to that 
   window.
------------------------------------------------------------------------*/

DGWindow* DGGui::GetWindow(UINT windowID)
{
   return mainWindow->GetWindow(windowID);
}

/*------------------------------------------------------------------------
Function Name: SetWindowFocus
Parameters:
   UINT windowID : the ID of a window 
Description:
   This function receives a window ID and sets the focus to that window.
------------------------------------------------------------------------*/

void DGGui::SetWindowFocus(UINT windowID)
{
   //Inform the previously focused window that it is losing the focus
   if(focusedWindow != IDW_NONE)
      PostMessage(new DGMessage(GM_LOSEFOCUS, focusedWindow, 0, 0, 
         windowID));

   //Inform the newly focused window that it is gaining the focus
   if(windowID != IDW_NONE)
      PostMessage(new DGMessage(GM_FOCUS, windowID, 0, 0, 
         focusedWindow));

   focusedWindow = windowID;
   
}

/*------------------------------------------------------------------------
Function Name: GetWindowFocus
Parameters:
Description:
   This function returns the window ID of the window with the focus.
   If no window currently has the focus, IDW_NONE is returned.
------------------------------------------------------------------------*/

UINT DGGui::GetWindowFocus()
{
   return focusedWindow;
}

/*------------------------------------------------------------------------
Function Name: RemoveWindowFocus
Parameters:
Description:
   This function removes the focus from the window that currently has
   it and sets the focus to IDW_NONE, meaning no window has the focus.
------------------------------------------------------------------------*/

void DGGui::RemoveWindowFocus()
{
   //Inform the previously focused window that it is losing the focus
   if(focusedWindow != IDW_NONE)
      PostMessage(new DGMessage(GM_LOSEFOCUS, focusedWindow, 0, 0, IDW_NONE));

   focusedWindow = IDW_NONE;
}

/*------------------------------------------------------------------------
Function Name: SetMouseCapture
Parameters:
Description:
   This function sets the window that is capturing the mouse. When a
   window captures the mouse, it receives all mouse messages, no matter
   where the mouse actually is.
------------------------------------------------------------------------*/

void DGGui::SetMouseCapture(UINT windowID)
{
   mouseCaptureWinID = windowID;
}

/*------------------------------------------------------------------------
Function Name: ReleaseMouseCapture
Parameters:
Description:
   This function releases any mouse capture that is set. Afterward,
   the mouse messages only go to the window which is directly under the
   mouse cursor.
------------------------------------------------------------------------*/

void DGGui::ReleaseMouseCapture()
{
   mouseCaptureWinID = IDW_NONE;
}

/*------------------------------------------------------------------------
Function Name: GetMouseCapture
Parameters:
Description:
   This function returns the ID of the window that has captured the mouse.
   If no window is currently capturing the mouse, IDW_NONE is returned.
------------------------------------------------------------------------*/

UINT DGGui::GetMouseCapture()
{
   return mouseCaptureWinID;
}

/*------------------------------------------------------------------------
Function Name: CreateTimer
Description:
   This function creates a timer associated with timerID with an interval
   of interval milliseconds. The timer messages are send to windows
   with an ID of windowID.
Parameters:
   UINT timerID : A unique ID for a timer
   UINT windowID : The ID of a window
   UINT interval : The number of milliseconds between timer messages
------------------------------------------------------------------------*/

void DGGui::CreateTimer(UINT timerID, UINT windowID, UINT interval)
{
   HWND hWnd = DGGetApp()->GetWindowsHandle();
   ::SetTimer(hWnd, timerID, interval, NULL);
   timerTable.insert(TimerEntry(timerID, windowID));
}

/*------------------------------------------------------------------------
Function Name: DestroyTimer
Description:
   This function destroy a timer associated with timerID.
Parameters:
   UINT timerID : A unique ID for a timer
------------------------------------------------------------------------*/

void DGGui::DestroyTimer(UINT timerID)
{
   ::KillTimer(DGGetApp()->GetWindowsHandle(), timerID);
   timerTable.erase(timerID);
}

/*------------------------------------------------------------------------
Function Name: DrawGUI
Parameters:
Description:
   This function causes the windows of the GUI to draw themselves on the
   screen.
------------------------------------------------------------------------*/

void DGGui::DrawGUI()
{
   mainWindow->DrawWindow();
}