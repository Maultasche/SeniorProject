/*------------------------------------------------------------------------
File Name: DGTitleBar.cpp
Description: This file contains the implementation of the DGTitleBar 
   class, which is a control that holds the title of a window as well 
   allows the window to be moved.
Version:
   1.0.0    19.09.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"


DGTitleBar::DGTitleBar(UINT winID, DGWindow* parentWin, const int xPos, 
                       const int yPos,  const int width, const int height,
                       char* text, DGFont font) :
   DGButton(winID, parentWin, xPos, yPos, width, height, BT_PUSHBUTTON | 
      BT_TEXTBUTTON, text, font)
{
   SetWindowType(WT_TITLEBAR);
}

DGTitleBar::DGTitleBar(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
                       char* text, DGFont font) :
   DGButton(winID, parentWin, dimensions, BT_PUSHBUTTON | BT_TEXTBUTTON, 
      text, font)
{
   SetWindowType(WT_TITLEBAR);
}

DGTitleBar::DGTitleBar(UINT winID, DGWindow* parentWin, const DGPoint& position, 
                       const DGPoint& size, char* text, DGFont font) :
   DGButton(winID, parentWin, position, size, BT_PUSHBUTTON | BT_TEXTBUTTON, 
      text, font)
{
   SetWindowType(WT_TITLEBAR);
}

/*Overridden methods*/

void FC DGTitleBar::OnCreate()
{
   DGButton::OnCreate();
}

void FC DGTitleBar::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   //If there was no pressure before the button goes down,
   //then we need to send a GM_TITLEBAR_DOWN message
   if(!GetPressure())
   {
      DGMessage* msg = new DGMessage(GM_TITLEBAR_DOWN, 
         GetParent()->GetWindowID(), 0, 0, GetWindowID());
      GetParent()->SendMessage(msg);
      delete msg;
   }

   DGButton::OnLButtonDown(x, y, keyboardState);

   //We need to keep track of the mouse movement in absolute coords
   //Relative coords will always be the same when it is moving
   previousPosition = RelToAbsCoords(x, y);
   DGGetGui()->SetMouseCapture(GetWindowID());
}

void FC DGTitleBar::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   DGButton::OnLButtonUp(x, y, keyboardState);

   DGGetGui()->ReleaseMouseCapture();
}

void FC DGTitleBar::OnMouseMove(int x, int y, BYTE* keyboardState)
{
   DGButton::OnMouseMove(x, y, keyboardState);

   if(GetPressure())
   {
      //Translate the current position of the mouse to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      DGPoint windowMovement(absoluteCoords.x - previousPosition.x, 
         absoluteCoords.y - previousPosition.y);

      previousPosition = absoluteCoords;

      //Change the position of the parent relative to how the mouse
      //cursor moved
      DGPoint windowPosition = GetParent()->GetPosition();
      windowPosition.Offset(windowMovement.x, windowMovement.y);
      GetParent()->SetPosition(windowPosition);
   }
}