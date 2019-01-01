/*------------------------------------------------------------------------
File Name: DGButton.cpp
Description: This file contains the implementation of the DGButton class, 
   which is a a button control. DGButton can be used for any button which 
   has 2 states (depressed and normal), such as a normal push button, 
   a radio button, or check box.
Version:
   1.0.0    25.08.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

#define BN_EDGE_WIDTH               2

#define BN_DEFAULT_TEXT_RED         0
#define BN_DEFAULT_TEXT_GREEN       0
#define BN_DEFAULT_TEXT_BLUE        0

#define BN_DEFAULT_BUTTON_RED       180
#define BN_DEFAULT_BUTTON_GREEN     180
#define BN_DEFAULT_BUTTON_BLUE      180

DGButton::DGButton(UINT winID, DGWindow* parentWin) :
   DGWindow(winID, true),
   buttonState(BS_NORMAL),
   buttonType(BT_PUSHBUTTON),
   enabled(true),
   pressure(false),
   edgeWidth(BN_EDGE_WIDTH),
   textColor(DGColor(BN_DEFAULT_TEXT_RED, BN_DEFAULT_TEXT_GREEN, 
   BN_DEFAULT_TEXT_BLUE)),
   buttonColor(DGColor(BN_DEFAULT_BUTTON_RED, BN_DEFAULT_BUTTON_GREEN, 
   BN_DEFAULT_BUTTON_BLUE)),
   displayWindow(NULL)

{
   SetWindowType(WT_BUTTON);
   SetParent(parentWin);
}

DGButton::DGButton(UINT winID, DGWindow* parentWin, const int xPos, 
                   const int yPos,  const int width, const int height,
                   UINT aButtonType,  char* text, DGFont font) :
   DGWindow(winID, true, xPos, yPos, width, height),
   buttonState(BS_NORMAL),
   buttonType(aButtonType),
   enabled(true),
   pressure(false),
   buttonFont(font),
   edgeWidth(BN_EDGE_WIDTH),
   textColor(DGColor(BN_DEFAULT_TEXT_RED, BN_DEFAULT_TEXT_GREEN, 
   BN_DEFAULT_TEXT_BLUE)),
   buttonColor(DGColor(BN_DEFAULT_BUTTON_RED, BN_DEFAULT_BUTTON_GREEN, 
   BN_DEFAULT_BUTTON_BLUE)),
   displayWindow(NULL)   
{
   SetWindowType(WT_BUTTON);
   SetParent(parentWin);

   strcpy(buttonText, text);
}

DGButton::DGButton(UINT winID, DGWindow* parentWin, 
                   const DGArea& dimensions, UINT aButtonType, 
                   char* text, DGFont font) :
   DGWindow(winID, true, dimensions),
   buttonState(BS_NORMAL),
   buttonType(aButtonType),
   enabled(true),
   pressure(false),
   buttonFont(font),
   edgeWidth(BN_EDGE_WIDTH),
   textColor(DGColor(BN_DEFAULT_TEXT_RED, BN_DEFAULT_TEXT_GREEN, 
   BN_DEFAULT_TEXT_BLUE)),
   buttonColor(DGColor(BN_DEFAULT_BUTTON_RED, BN_DEFAULT_BUTTON_GREEN, 
   BN_DEFAULT_BUTTON_BLUE)),
   displayWindow(NULL)  
{
   SetWindowType(WT_BUTTON);
   SetParent(parentWin);

   strcpy(buttonText, text);
}

DGButton::DGButton(UINT winID, DGWindow* parentWin, const DGPoint& position, 
                   const DGPoint& size, UINT aButtonType, char* text, 
                   DGFont font) :
   DGWindow(winID, true, position, size),
   buttonState(BS_NORMAL),
   buttonType(aButtonType),
   enabled(true),
   pressure(false),
   buttonFont(font),
   edgeWidth(BN_EDGE_WIDTH),
   textColor(DGColor(BN_DEFAULT_TEXT_RED, BN_DEFAULT_TEXT_GREEN, 
   BN_DEFAULT_TEXT_BLUE)),
   buttonColor(DGColor(BN_DEFAULT_BUTTON_RED, BN_DEFAULT_BUTTON_GREEN, 
   BN_DEFAULT_BUTTON_BLUE)),
   displayWindow(NULL)  
{
   SetWindowType(WT_BUTTON);
   SetParent(parentWin);

   strcpy(buttonText, text);
}

/*------------------------------------------------------------------------
Function Name: SetFont
Description:
   This function sets the font that the button uses when it displays
   text.
Parameters: DGFont font - the font to be used
Preconditions: The button has the style BT_TEXTBUTTON
------------------------------------------------------------------------*/

void DGButton::SetFont(DGFont font)
{
   assert(buttonType == BT_TEXTBUTTON);

   buttonFont = font;
   ((DGLabel*)displayWindow)->SetFont(buttonFont);
}

/*------------------------------------------------------------------------
Function Name: GetFont
Description:
   This function returns the font that the button uses when it displays
   text.
Parameters:
Returns:
   The font to be used when the button displays text
Preconditions: The button has the style BT_TEXTBUTTON
------------------------------------------------------------------------*/

DGFont DGButton::GetFont()
{
   assert(buttonType == BT_TEXTBUTTON);

   return buttonFont;
}

/*------------------------------------------------------------------------
Function Name: SetText
Description:
   This function sets the text the button displays when it has the style
   BT_TEXTBUTTON.
Parameters: char* text - pointer to an arry holding the text to be 
   displayed
Preconditions: The button has the style BT_TEXTBUTTON
------------------------------------------------------------------------*/

void DGButton::SetText(const char* text)
{
   assert(buttonType == BT_TEXTBUTTON);

   strcpy(buttonText, text);
   ((DGLabel*)displayWindow)->SetText(buttonText);
}

/*------------------------------------------------------------------------
Function Name: GetText
Description:
   This function returns the text the button displays when it has the 
   style BT_TEXTBUTTON.
Parameters: 
Returns:
   The text that the button is using
Preconditions: The button has the style BT_TEXTBUTTON
------------------------------------------------------------------------*/

char* const DGButton::GetText()
{
   assert(buttonType == BT_TEXTBUTTON);

   return buttonText;
}

/*------------------------------------------------------------------------
Function Name: SetState
Description:
   This function sets the state of the button.
Parameters: 
   UINT state - the state that the button is to be set to
------------------------------------------------------------------------*/

void DGButton::SetState(UINT state)
{
   buttonState = state;
}

/*------------------------------------------------------------------------
Function Name: SetType
Description:
   This function sets the type of the button. The button type may be any
   bitwise OR combination of the button type flags defined in DGButton.h.
Parameters: 
   UINT state - the type that the button is to be set to
------------------------------------------------------------------------*/

void DGButton::SetType(UINT type)
{
   //Change the display window depending on the type of button

   buttonType = type;
}

/*------------------------------------------------------------------------
Function Name: SetTextColor
Description:
   This function sets the color of the text that the button displays when
   it is of type BT_TEXTBUTTON.
Parameters: DGColor& color - the color to be used in drawing text
Preconditions: The button has the style BT_TEXTBUTTON
------------------------------------------------------------------------*/

void DGButton::SetTextColor(DGColor& color)
{
   assert(buttonType == BT_TEXTBUTTON);

   ((DGLabel*)displayWindow)->SetForegroundColor(color);
}

/*------------------------------------------------------------------------
Function Name: SetButtonColor
Description:
   This function sets the color of the button.
Parameters: DGColor& color - the color to be used in drawing the button
------------------------------------------------------------------------*/

void DGButton::SetButtonColor(DGColor& color)
{
   buttonColor = color;
}

/*------------------------------------------------------------------------
Function Name: IsDisplayingImage
Description:
   This function returns whether this button is currently displaying an
   image. A button with a BT_IMAGEBUTTON style will only display an image 
   if it has been given the ID of a bitmap that is loaded.
Returns: true if the button is currently displaying an image, false 
   if the button is not displaying an image
------------------------------------------------------------------------*/

bool DGButton::IsDisplayingImage()
{
   bool displayingImage = false;

   if(buttonType & BT_IMAGEBUTTON)
   {
      if(displayWindow != NULL && 
         displayWindow->GetWindowType() == WT_IMAGE)
         displayingImage = true;
   }

   return displayingImage;
}

/*------------------------------------------------------------------------
Function Name: SetBitmapID
Description:
   This function sets bitmap to be displayed in the button. This only has
   an effect when the button control has BT_IMAGEBUTTON style.
Parameters: UINT bitmapID - the ID of the bitmap to be displayed
Preconditions: A bitmap assigned to bitmapID must be loaded
------------------------------------------------------------------------*/

void DGButton::SetBitmapID(UINT bitmapID)
{  
   if(buttonType & BT_IMAGEBUTTON)
   {
      //Delete the previous image
      if(displayWindow != NULL)
      {
         DestroyWindow(displayWindow->GetWindowID());
      }

      //Check to see if the bitmap is loaded
      DGBitmap* bitmap = dgGraphics->GetBitmap(bitmapID);

      if(bitmap != NULL)
      {
         DGPoint buttonSize = GetSize();
         buttonSize.Offset(-(BN_EDGE_WIDTH << 1), -(BN_EDGE_WIDTH << 1));

         DGArea childWindowArea(DGPoint(BN_EDGE_WIDTH, BN_EDGE_WIDTH), 
            buttonSize);

         //It looks a bit better in 16x16 if we offset it by 1
         childWindowArea.Offset(1, 1);

         displayWindow = new DGImage(IDW_BN_CHILDWINDOW, this, 
            childWindowArea, bitmapID, true, DGColor(255, 255, 255));

         AddChildWindow(displayWindow);
      }
         
   }
}

/*------------------------------------------------------------------------
Function Name: GetBitmapID
Description:
   This function returns the ID of the image that is displayed in the
   button.
Returns: The bitmap ID of the image displayed in the button
Preconditions: IsDisplayingImage() returns true
------------------------------------------------------------------------*/

UINT DGButton::GetBitmapID()
{
   assert(IsDisplayingImage());

   return ((DGImage*)displayWindow)->GetBitmapID();
}

/*Overridden methods*/

void FC DGButton::OnDrawWindow(DGWindowSurface* surface)
{
   if(buttonState == BS_NORMAL && !pressure)
   {
      if(enabled)
         OnDrawNormal(surface);
      else
         OnDrawNormalDisabled(surface);
   }
   else
   {
      if(enabled)
         OnDrawDepressed(surface);
      else
         OnDrawDepressedDisabled(surface);
   }
}

void FC DGButton::OnCreate()
{
   DGPoint buttonSize = GetSize();
   buttonSize.Offset(-(BN_EDGE_WIDTH << 1), -(BN_EDGE_WIDTH << 1));

   DGArea childWindowArea(DGPoint(BN_EDGE_WIDTH, BN_EDGE_WIDTH), 
      buttonSize);

   if(buttonType & BT_TEXTBUTTON)
   {
      displayWindow = new DGLabel(IDW_BN_CHILDWINDOW, this, 
         childWindowArea, buttonText, true, 
         DGColor(0, 0, 0), DGColor(255, 0, 0),
         DT_CENTER | DT_WORDBREAK | DT_SINGLELINE | DT_VCENTER, buttonFont, true);
  
      AddChildWindow(displayWindow);

      AddMessageHandler(GM_LABEL_LBUTTONDOWN, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

      AddMessageHandler(GM_LABEL_LBUTTONUP, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

      AddMessageHandler(GM_LABEL_LBUTTONDBLCLK, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

      AddMessageHandler(GM_LABEL_MOUSEMOVE, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

   }
   else if(buttonType & BT_IMAGEBUTTON)
   {
      AddMessageHandler(GM_IMAGE_LBUTTONDOWN, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

      AddMessageHandler(GM_IMAGE_LBUTTONUP, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

      AddMessageHandler(GM_IMAGE_LBUTTONDBLCLK, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

      AddMessageHandler(GM_IMAGE_MOUSEMOVE, 
         new MsgHandlerFunction<DGButton>(this, OnChildWindowMessage));

   }
}

void FC DGButton::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   //Only do something if the button is enabled
   if(enabled)
   {
      DGMessage* msg;

      //If there was no pressure before, tell the button it is 
      //under pressure and send a button down message to the parent
      if(!pressure)
      {
         msg = new DGMessage(GM_BUTTON_DOWN,
            GetParent()->GetWindowID(), 0, 0, GetWindowID());
         GetParent()->SendMessage(msg);
         delete msg;

         pressure = true;
      }

      //Send a button pressure message to the parent
      msg = new DGMessage(GM_BUTTON_PRESSURE,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());
      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGButton::OnLButtonDblClk(int x, int y, BYTE* keyboardState)
{
   //A double click is considered the same as a down button
   OnLButtonDown(x, y, keyboardState);
}

void FC DGButton::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   //Only do something if the the button is enabled
   if(enabled)
   {
      //Tell the button is no longer under pressure
      pressure = false;

      //Change the state only if this button is a toggle button
      if(buttonType & BT_TOGGLEBUTTON)
      {
         if(buttonState == BS_NORMAL)
            buttonState = BS_DEPRESSED;
         else
            buttonState = BS_NORMAL;
      }

      //Tell the parent that the button was clicked
      DGGetGui()->PostMessage(new DGMessage(GM_BUTTON_CLICKED,
         GetParent()->GetWindowID(), 0, 0, GetWindowID()));
   }
}

void FC DGButton::OnMouseLeave(int x, int y, BYTE* keyboardState)
{
   //When the mouse leaves the window, any pressure is automatically
   //removed
   pressure = false;
}

void FC DGButton::OnWindowSizing()
{
   OnWindowSized();
}

void FC DGButton::OnWindowSized()
{
   //Size the display window so that it is the size of the button
   //minus the size of the edges on all sides
   if(displayWindow != NULL)
   {
      DGPoint buttonSize = GetSize();
      buttonSize.Offset(-(BN_EDGE_WIDTH << 1), -(BN_EDGE_WIDTH << 1));
      displayWindow->SetSize(buttonSize);
   }
}

void DGButton::OnChildWindowMessage(DGMessage* msg)
{
   //We need to change the message type and destination and have this
   //window handle the message
   msg->destination = GetWindowID();

   switch(msg->messageType)
   {
   case GM_LABEL_LBUTTONDOWN:
   case GM_IMAGE_LBUTTONDOWN:
      msg->messageType = GM_LBUTTONDOWN;
      break;
   case GM_LABEL_LBUTTONUP:
   case GM_IMAGE_LBUTTONUP:
      msg->messageType = GM_LBUTTONUP;
      break;
   case GM_LABEL_LBUTTONDBLCLK:
   case GM_IMAGE_LBUTTONDBLCLK:
      msg->messageType = GM_LBUTTONDBLCLK;
      break;
   case GM_LABEL_MOUSEMOVE:
   case GM_IMAGE_MOUSEMOVE:
      msg->messageType = GM_MOUSEMOVE;
      break;
   }

   HandleMessage(msg);
}

/*Overridable methods*/

/*------------------------------------------------------------------------
Function Name: OnDrawNormal
Description:
   This function draws the button in its normal enabled state
Parameters: DGWindowSurface* surface - the window surface to draw upon
------------------------------------------------------------------------*/

void FC DGButton::OnDrawNormal(DGWindowSurface* surface)
{
   //Fill the surface with the button color
   surface->FillSurface(buttonColor);

   DGPoint size = GetSize();
   DGColor darkenedColor = buttonColor.Darken(50);
   DGColor lightenedColor = buttonColor.Lighten(50);
   DGColor drawColor;

   surface->LockSurface();

   //Draw the edges of the button
   for(UINT i = 0; i < edgeWidth; i++)
   {
      surface->DrawVerticalLine(0 + i, 0 + i, size.y - i - 1, 
         lightenedColor);
      surface->DrawHorizontalLine(0 + i, size.x - i - 1, 0 + i,
         lightenedColor);
      surface->DrawVerticalLine(size.x - i - 1, 0 + i + 1, size.y - i - 1,
         darkenedColor);
      surface->DrawHorizontalLine(0 + i + 1, size.x - i - 1, size.y - i - 1,
         darkenedColor);
   }

   surface->UnlockSurface();
}

/*------------------------------------------------------------------------
Function Name: OnDrawNormalDisabled
Description:
   This function draws the button in its normal disabled state
Parameters: DGWindowSurface* surface - the window surface to draw upon
------------------------------------------------------------------------*/

void FC DGButton::OnDrawNormalDisabled(DGWindowSurface* surface)
{

}

/*------------------------------------------------------------------------
Function Name: OnDrawDepressed
Description:
   This function draws the button in its depressed enabled state
Parameters: DGWindowSurface* surface - the window surface to draw upon
------------------------------------------------------------------------*/

void FC DGButton::OnDrawDepressed(DGWindowSurface* surface)
{
   //Fill the surface with the button color
   surface->FillSurface(buttonColor);

   DGPoint size = GetSize();
   DGColor darkenedColor = buttonColor.Darken(50);
   DGColor lightenedColor = buttonColor.Lighten(50);

   surface->LockSurface();

   //Draw the edges of the button
   for(UINT i = 0; i < edgeWidth; i++)
   {
      surface->DrawVerticalLine(0 + i, 0 + i, size.y - i - 1, 
         darkenedColor);
      surface->DrawHorizontalLine(0 + i, size.x - i - 1, 0 + i,
         darkenedColor);
      surface->DrawVerticalLine(size.x - i - 1, 0 + i + 1, size.y - i - 1,
         lightenedColor);
      surface->DrawHorizontalLine(0 + i + 1, size.x - i - 1, size.y - i - 1,
         lightenedColor);
   }

   surface->UnlockSurface();
}

/*------------------------------------------------------------------------
Function Name: OnDrawDepressedDisabled
Description:
   This function draws the button in its depressed disabled state
Parameters: DGWindowSurface* surface - the window surface to draw upon
------------------------------------------------------------------------*/

void FC DGButton::OnDrawDepressedDisabled(DGWindowSurface* surface)
{

}

