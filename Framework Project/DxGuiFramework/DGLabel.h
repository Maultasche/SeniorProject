/*------------------------------------------------------------------------
File Name: DGLabel.h
Description: This file contains the DGLabel class, which is a control that
   displays text.
Version:
   1.0.0    11.07.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGLABEL_H
#define DGLABEL_H

#define LABEL_DEFAULT_FONT_HEIGHT   16

class DGLabel : public DGWindow
{
public:
   DGLabel(UINT winID, DGWindow* parentWin);
   DGLabel(UINT winID, DGWindow* parentWin, const int xPos, 
      const int yPos,  const int width, const int height,
      char* text = "", bool transparent = false, 
      DGColor foreColor = DGColor(255, 255, 255), 
      DGColor backColor = DGColor(0, 0, 0), 
      UINT flags = DT_SINGLELINE | DT_LEFT, 
      DGFont _font = DGFont("MS Sans Serif", LABEL_DEFAULT_FONT_HEIGHT),
      bool _parentNotify = true);

   DGLabel(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
      char* text = "", bool transparent = false, 
      DGColor foreColor = DGColor(255, 255, 255), 
      DGColor backColor = DGColor(0, 0, 0), 
      UINT flags = DT_SINGLELINE | DT_LEFT, 
      DGFont _font = DGFont("MS Sans Serif", LABEL_DEFAULT_FONT_HEIGHT),
      bool _parentNotify = true);

   DGLabel(UINT winID, DGWindow* parentWin, const DGPoint& position, 
      const DGPoint& size, 
      char* text = "", bool transparent = false, 
      DGColor foreColor = DGColor(255, 255, 255), 
      DGColor backColor = DGColor(0, 0, 0), 
      UINT flags = DT_SINGLELINE | DT_LEFT, 
      DGFont _font = DGFont("MS Sans Serif", LABEL_DEFAULT_FONT_HEIGHT),
      bool _parentNotify = true);

   void SetTransparency(bool transparent)
   {transparentBackground = transparent;}
   bool GetTransparency(void) {return transparentBackground;}

   void SetParentNotify(bool notify) {parentNotify = notify;}
   bool GetParentNotify(void) {return parentNotify;}

   void SetForegroundColor(DGColor color) {foregroundColor = color;}
   DGColor GetForegroundColor(void) {return foregroundColor;}

   void SetBackgroundColor(DGColor color) {backgroundColor = color;}
   DGColor GetBackgroundColor(void) {return backgroundColor;}

   void SetFlags(UINT flags) {textFlags = flags;}
   UINT GetFlags(void) {return textFlags;}

   void SetFont(DGFont aFont) {font = aFont;}
   DGFont GetFont(void) {return font;}

   void SetText(const char* aText) {strcpy(text, aText);}
   char* const GetText(void) {return text;}

protected:
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnLButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnMButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnMButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnMButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnRButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnRButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnRButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnMouseMove(int x, int y, BYTE* keyboardState);

private:
   bool transparentBackground;
   bool parentNotify;
   DGColor foregroundColor;
   DGColor backgroundColor;
   UINT textFlags;  //The same flags as in the DrawText() WinAPI function
   DGFont font;

   char text[1000];
};

#endif