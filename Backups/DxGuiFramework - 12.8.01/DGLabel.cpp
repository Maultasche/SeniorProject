/*------------------------------------------------------------------------
File Name: DGLabel.cpp
Description: This file contains the implementation of the DGLabel class, 
   which is a control that displays text.
Version:
   1.0.0    11.07.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"


DGLabel::DGLabel(UINT winID, DGWindow* parentWin) : 
   DGWindow(winID, true)
{
   
   SetWindowType(WT_LABEL);
   SetParent(parentWin);
}

DGLabel::DGLabel(UINT winID, DGWindow* parentWin, const int xPos, 
                 const int yPos, const int width, 
                 const int height, char* text, bool transparent, 
                 DGColor foreColor, DGColor backColor, 
                 UINT flags, DGFont font, bool parentNotify) :
   DGWindow(winID, true, xPos, yPos, width, height)
{
   SetWindowType(WT_LABEL);
   SetParent(parentWin);

   strcpy(this->text, text);
   transparentBackground = transparent;
   foregroundColor = foreColor;
   backgroundColor = backColor;
   textFlags = flags;
   this->font = font;
   this->parentNotify = parentNotify;
}

DGLabel::DGLabel(UINT winID, DGWindow* parentWin, 
                 const DGArea& dimensions,
                 char* text, bool transparent, 
                 DGColor foreColor, DGColor backColor, 
                 UINT flags, DGFont font, bool parentNotify) :
   DGWindow(winID, true, dimensions)
{
   SetWindowType(WT_LABEL);
   SetParent(parentWin);

   strcpy(this->text, text);
   transparentBackground = transparent;
   foregroundColor = foreColor;
   backgroundColor = backColor;
   textFlags = flags;
   this->font = font;
   this->parentNotify = parentNotify;
}

DGLabel::DGLabel(UINT winID, DGWindow* parentWin,
                 const DGPoint& position, const DGPoint& size, 
                 char* text, bool transparent, 
                 DGColor foreColor, DGColor backColor, 
                 UINT flags, DGFont font, bool parentNotify) :
   DGWindow(winID, true, position, size)
{
   SetWindowType(WT_LABEL);
   SetParent(parentWin);

   strcpy(this->text, text);
   transparentBackground = transparent;
   foregroundColor = foreColor;
   backgroundColor = backColor;
   textFlags = flags;
   this->font = font;
   this->parentNotify = parentNotify;
}

void FC DGLabel::OnDrawWindow(DGSurface* surface)
{
   if(!transparentBackground)
      surface->FillSurface(backgroundColor);

   DGPoint surfaceSize = surface->GetSize();
   surface->DrawText(text, DGRectangle(0, 0, surfaceSize.x - 1, 
      surfaceSize.y - 1), textFlags);
}

void FC DGLabel::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_LBUTTONDOWN,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_LBUTTONUP,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnLButtonDblClk(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_LBUTTONDBLCLK,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnMButtonDown(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_MBUTTONDOWN,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnMButtonUp(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_MBUTTONUP,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnMButtonDblClk(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_MBUTTONDBLCLK,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnRButtonDown(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_RBUTTONDOWN,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnRButtonUp(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_RBUTTONUP,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}

void FC DGLabel::OnRButtonDblClk(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
      DGGetGui()->PostMessage(new DGMessage(GM_LABEL_RBUTTONDBLCLK,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
}
