/*------------------------------------------------------------------------
File Name: DGTitleBar.h
Description: This file contains the DGTitleBar class, which is a control
   that holds the title of a window as well allows the window to be 
   moved.
Version:
   1.0.0    19.09.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGTITLEBAR_H
#define DGTITLEBAR_H

//The ID of the child button, which is only visible inside the
//title bar control
#define IDW_TB_CHILDWINDOW       100

#define DGTITLEBAR_DEFAULT_FONT_HEIGHT   16

class DGTitleBar : public DGButton
{
public:
   DGTitleBar(UINT winID, DGWindow* parentWin, const int xPos, 
      const int yPos,  const int width, const int height,
      char* text = "", 
      DGFont font = DGFont("MS Sans Serif", DGTITLEBAR_DEFAULT_FONT_HEIGHT));

   DGTitleBar(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
      char* text = "", 
      DGFont font = DGFont("MS Sans Serif", DGTITLEBAR_DEFAULT_FONT_HEIGHT));

   DGTitleBar(UINT winID, DGWindow* parentWin, const DGPoint& position, 
      const DGPoint& size, char* text = "", 
      DGFont font = DGFont("MS Sans Serif", DGTITLEBAR_DEFAULT_FONT_HEIGHT));

protected:
   void FC OnCreate(void);
   void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnMouseMove(int x, int y, BYTE* keyboardState);

   void OnChildButtonMessage(DGMessage* msg);

private:
   DGPoint previousPosition;
};

#endif