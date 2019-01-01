/*------------------------------------------------------------------------
File Name: DGInput.h
Description: This file contains the DGInput class, which collects and
   stores input events, so that they can be passed on to the GUI, which
   converts them into input messages.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

class InputEvent
{
public:
   InputEvent()
   {
      messageType = 0;
      wParam = 0;
      lParam = 0;
   }

   InputEvent(UINT message, UINT w_param, UINT l_param, BYTE* keyStateArray)
   {
      messageType = message;
      wParam = w_param;
      lParam = l_param;
      memcpy(&keyboardState, keyStateArray, 256);
   }

   UINT messageType;
   UINT wParam;
   UINT lParam;
   BYTE keyboardState[256];
};


class DGInput
{
public:
   DGInput();
   virtual ~DGInput();

   void FC CreateEvent(UINT msg, WPARAM wparam, LPARAM lparam,
      BYTE* keyboardState);
   InputEvent* FC GetEvent(void);
   InputEvent* FC RemoveEvent(void);

   void FC ClearEventQueue(void) {inputQueue.DeleteAll();}
   bool FC EventsInQueue(void) 
   {return (inputQueue.GetNumOfItems() > 0);}

private:
   DGQueue<InputEvent> inputQueue;
};