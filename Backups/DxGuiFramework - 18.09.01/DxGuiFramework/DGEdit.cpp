/*------------------------------------------------------------------------
File Name: DGEdit.cpp
Description: This file contains the implementation of the DGEdit class, 
   which is a control that allows the user to input text.
Version:
   1.0.0    17.09.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

/*Constructors*/

DGEdit::DGEdit(UINT winID, DGWindow* parentWin) :
   DGWindow(winID, true)
{
   SetWindowType(WT_EDIT);
   SetParent(parentWin);
}

DGEdit::DGEdit(UINT winID, DGWindow* parentWin, const int xPos, 
               const int yPos,  const int width, const int height,
               char* _text, DGColor foreColor, DGColor backColor, 
               DGFont _font, bool _parentNotify) :
   DGWindow(winID, true, xPos, yPos, width, height)
{
   SetWindowType(WT_EDIT);
   SetParent(parentWin);

   strcpy(text, _text);
   foregroundColor = foreColor;
   backgroundColor = backColor;
   font = _font;
   parentNotify = _parentNotify;
}

DGEdit::DGEdit(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
               char* _text, DGColor foreColor, DGColor backColor, 
               DGFont _font, bool _parentNotify) :
   DGWindow(winID, true, dimensions)
{
   SetWindowType(WT_EDIT);
   SetParent(parentWin);

   strcpy(text, _text);
   foregroundColor = foreColor;
   backgroundColor = backColor;
   font = _font;
   parentNotify = _parentNotify;
}

DGEdit::DGEdit(UINT winID, DGWindow* parentWin, const DGPoint& position, 
               const DGPoint& size, char* _text, DGColor foreColor, 
               DGColor backColor, DGFont _font, bool _parentNotify) :
   DGWindow(winID, true, position, size)
{
   SetWindowType(WT_EDIT);
   SetParent(parentWin);

   strcpy(text, _text);
   foregroundColor = foreColor;
   backgroundColor = backColor;
   font = _font;
   parentNotify = _parentNotify;   
}

/*Overridden message-handling methods*/

void FC DGEdit::OnDrawWindow(DGWindowSurface* surface)
{
   //Draw the background
   surface->FillSurface(backgroundColor);

   surface->LockSurface();

   //Draw the border around the edit control
   DGPoint size = GetSize();
   surface->DrawRectangle(DGRectangle(0, 0, size.x - 1, size.y - 1), 
      foregroundColor);

   surface->UnlockSurface();
/*   if(!transparentBackground)
      surface->FillSurface(backgroundColor);

   surface->SetTextColor(foregroundColor);

   DGPoint surfaceSize = GetSize();
   surface->DrawText(text, DGRectangle(0, 0, surfaceSize.x - 1, 
      surfaceSize.y - 1), textFlags);*/
}

void FC DGEdit::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_LBUTTONDOWN,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGEdit::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_LBUTTONUP,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGEdit::OnLButtonDblClk(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_LBUTTONDBLCLK,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}
