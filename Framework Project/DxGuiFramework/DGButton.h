/*------------------------------------------------------------------------
File Name: DGButton.h
Description: This file contains the DGButton class, which is a button
   control. DGButton can be used for any button which has 2 states 
   (depressed and normal), such as a normal push button, a radio button,
   or check box
Version:
   1.0.0    25.08.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGBUTTON_H
#define DGBUTTON_H

//The button states
#define BS_NORMAL       0
#define BS_DEPRESSED    2


//These styles can be combined with a bitwise OR
#define BT_PUSHBUTTON            0x00000001
#define BT_TOGGLEBUTTON          0x00000002
#define BT_TEXTBUTTON            0x00000004
#define BT_IMAGEBUTTON           0x00000008

//The ID of the button's child window, which is only visible inside the
//button control
#define IDW_BN_CHILDWINDOW             100

#define BUTTON_DEFAULT_FONT_HEIGHT     16
#define BUTTON_DEFAULT_TEXT_LENGTH     256

class DGButton : public DGWindow
{
public:
   DGButton(UINT winID, DGWindow* parentWin);
   DGButton(UINT winID, DGWindow* parentWin, const int xPos, 
      const int yPos,  const int width, const int height,
      UINT buttonType = BT_PUSHBUTTON | BT_TEXTBUTTON,  char* text = "", 
      DGFont font = DGFont("MS Sans Serif", BUTTON_DEFAULT_FONT_HEIGHT));

   DGButton(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
      UINT buttonType = BT_PUSHBUTTON | BT_TEXTBUTTON, char* text = "", 
      DGFont font = DGFont("MS Sans Serif", BUTTON_DEFAULT_FONT_HEIGHT));

   DGButton(UINT winID, DGWindow* parentWin, const DGPoint& position, 
      const DGPoint& size, UINT buttonType = BT_PUSHBUTTON | BT_TEXTBUTTON,
      char* text = "", DGFont font = DGFont("MS Sans Serif", BUTTON_DEFAULT_FONT_HEIGHT));

   virtual void SetFont(DGFont font);
   DGFont GetFont(void);

   virtual void SetText(const char* text);
   char* const GetText(void);

   void SetState(UINT state);
   UINT GetState(void) {return buttonState;}

   void SetType(UINT type);
   UINT GetType(void) {return buttonType;}

   void SetEnabled(bool buttonEnabled) {enabled = buttonEnabled;}
   bool GetEnabled(void) {return enabled;}

   void SetTextColor(DGColor& color);
   DGColor GetTextColor(void) {return textColor;}

   void SetButtonColor(DGColor& color);
   DGColor GetButtonColor(void) {return buttonColor;}

   bool GetPressure(void) {return pressure;}

   bool IsDisplayingImage(void);
   void SetBitmapID(UINT bitmapID);
   UINT GetBitmapID(void);

protected:
   void FC OnCreate(void);
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnLButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnMouseLeave(int x, int y, BYTE* keyboardState);
   void FC OnWindowSizing(void);
   void FC OnWindowSized(void);

   virtual void OnChildWindowMessage(DGMessage* msg);

   virtual void FC OnDrawNormal(DGWindowSurface* surface);
   virtual void FC OnDrawNormalDisabled(DGWindowSurface* surface);
   virtual void FC OnDrawDepressed(DGWindowSurface* surface);
   virtual void FC OnDrawDepressedDisabled(DGWindowSurface* surface);

private:
   UINT buttonState;
   UINT buttonType;

   bool enabled;

   //This variable describes when pressure is being put upon the button,
   //which is when the mouse button is being held down when the mouse 
   //cursor is over the button
   bool pressure;

   DGFont buttonFont;
   char buttonText[BUTTON_DEFAULT_TEXT_LENGTH];

   DGColor textColor;
   DGColor buttonColor;

   //The width of the beveled edges of the button
   UINT edgeWidth;

   //The window (usually a label or image) that is to be displayed in
   //the center of the button
   DGWindow* displayWindow;
};

#endif