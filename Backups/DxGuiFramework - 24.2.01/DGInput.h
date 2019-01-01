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

};


class DGInput
{
public:
   DGInput();
   virtual ~DGInput();

   void FC CreateEvent(UINT msg, WPARAM wparam, LPARAM lparam);
   InputEvent* FC GetEvent(void);
   void FC RemoveEvent(void);

private:
   //InputEvent queue goes here
};