/*------------------------------------------------------------------------
File Name: DGEdit.h
Description: This file contains the DGEdit class, which is a control that
   allows the user to input text.
Version:
   1.0.0    16.09.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGEDIT_H
#define DGEDIT_H

#define DGEDIT_DEFAULT_FONT_HEIGHT   16
#define DGEDIT_DEFAULT_TEXT_LENGTH   1000

#define DGEDIT_BLINK_RATE            500

class DGEdit : public DGWindow
{
public:
   DGEdit(UINT winID, DGWindow* parentWin);
   DGEdit(UINT winID, DGWindow* parentWin, const int xPos, 
      const int yPos,  const int width, const int height,
      char* text = "",
      DGColor foreColor = DGColor(200, 200, 200), 
      DGColor backColor = DGColor(0, 0, 0), 
      DGFont _font = DGFont("MS Sans Serif", DGEDIT_DEFAULT_FONT_HEIGHT),
      bool _parentNotify = true);

   DGEdit(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
      char* text = "", 
      DGColor foreColor = DGColor(200, 200, 200), 
      DGColor backColor = DGColor(0, 0, 0), 
      DGFont _font = DGFont("MS Sans Serif", DGEDIT_DEFAULT_FONT_HEIGHT),
      bool _parentNotify = true);

   DGEdit(UINT winID, DGWindow* parentWin, const DGPoint& position, 
      const DGPoint& size, char* text = "", 
      DGColor foreColor = DGColor(200, 200, 200), 
      DGColor backColor = DGColor(0, 0, 0), 
      DGFont _font = DGFont("MS Sans Serif", DGEDIT_DEFAULT_FONT_HEIGHT),
      bool _parentNotify = true);

   void SetParentNotify(bool notify) {parentNotify = notify;}
   bool GetParentNotify(void) {return parentNotify;}

   void SetForegroundColor(DGColor color) {foregroundColor = color;}
   DGColor GetForegroundColor(void) {return foregroundColor;}

   void SetBackgroundColor(DGColor color) {backgroundColor = color;}
   DGColor GetBackgroundColor(void) {return backgroundColor;}

   void SetFont(DGFont aFont) {font = aFont;}
   DGFont GetFont(void) {return font;}

   void SetText(const char* aText) {strcpy(text, aText);}
   char* const GetText(void) {return text;}

protected:
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnLButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnCharacter(char character, PBYTE keyboardState);

private:
   bool parentNotify;
   DGColor foregroundColor;
   DGColor backgroundColor;
   DGFont font;
   
   int cursorBlinkRate;
   DWORD lastBlinkTime;
   bool cursorOn;

   char text[DGEDIT_DEFAULT_TEXT_LENGTH];
};

#endif