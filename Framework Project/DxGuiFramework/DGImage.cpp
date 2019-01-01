/*------------------------------------------------------------------------
File Name: DGImage.cpp
Description: This file contains the implementation of the DGImage class, 
   which is a control that displays a bitmap.
Version:
   1.0.0    09.09.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

DGImage::DGImage(UINT winID, DGWindow* parentWin, const int xPos, 
                 const int yPos, const int width, 
                 const int height, UINT _bitmapID, bool transparent, 
                 DGColor transparentColor, bool _parentNotify) :
   DGWindow(winID, true, xPos, yPos, width, height)
{
   SetWindowType(WT_IMAGE);
   SetParent(parentWin);

   bitmapID = _bitmapID;
   transparentBitmap = transparent;
   transparentColor = transparentColor;
   parentNotify = _parentNotify;

   bitmapOrigin = DGPoint(0, 0);
   strcpy(bitmapFileName, "");
}

DGImage::DGImage(UINT winID, DGWindow* parentWin, 
                 const DGArea& dimensions,
                 UINT _bitmapID, bool transparent, 
                 DGColor transparentColor, bool _parentNotify) :
   DGWindow(winID, true, dimensions)
{
   SetWindowType(WT_IMAGE);
   SetParent(parentWin);

   bitmapID = _bitmapID;
   transparentBitmap = transparent;
   transparentColor = transparentColor;
   parentNotify = _parentNotify;

   bitmapOrigin = DGPoint(0, 0);
   strcpy(bitmapFileName, "");
}

DGImage::DGImage(UINT winID, DGWindow* parentWin,
                 const DGPoint& position, const DGPoint& size, 
                 UINT _bitmapID, bool transparent, 
                 DGColor transparentColor, bool _parentNotify) :
   DGWindow(winID, true, position, size)
{
   SetWindowType(WT_IMAGE);
   SetParent(parentWin);

   bitmapID = _bitmapID;
   transparentBitmap = transparent;
   transparentColor = transparentColor;
   parentNotify = _parentNotify;

   bitmapOrigin = DGPoint(0, 0);
   strcpy(bitmapFileName, "");
}

/*------------------------------------------------------------------------
Function Name: LoadBitmapFile
Description:
   This function loads the bitmap contained in a bitmap file into the
   bitmap list. The bitmap is associated with the bitmap ID of this image
   control. If there already exists a bitmap in the GUI bitmap list with
   bitmapID, then that bitmap will be unloaded.
   The image control will display the bitmap if it was loaded
   successfully.
Parameters: const char* bitmapName - the name of a bitmap file from 
               which a bitmap is to be loaded.
            int priority - the priority of the bitmap to be loaded
Preconditions: bitmapName points to a null-terminated character array
------------------------------------------------------------------------*/

void DGImage::LoadBitmapFile(const char* bitmapName, int priority)
{
   //If there is a bitmap with this ID already in the bitmap list, 
   //then unload it
   dgGraphics->DeleteBitmap(bitmapID);

   dgGraphics->LoadBitmap(bitmapID, priority, bitmapName);
   strcpy(bitmapFileName, bitmapName);

   if(transparentBitmap)
   {
      DGBitmap* bitmap = dgGraphics->GetBitmap(bitmapID);
      assert(bitmap != NULL);
      bitmap->SetTransparentColor(transparentColor);
   }

   //Set the origin of the bitmap depending on whether it is smaller or
   //larger than the image control
/*   DGPoint bitmapSize = GetBitmapSize();
   DGPoint windowSize = GetSize();

   if(bitmapSize.x < windowSize.x)
      bitmapOrigin.x = (windowSize.x - bitmapSize.x) / 2;
   else
      bitmapOrigin.x = 0;

   if(bitmapSize.y < windowSize.y)
      bitmapOrigin.y = (windowSize.y - bitmapSize.y) / 2;
   else
      bitmapOrigin.y = 0;*/

   OnWindowSized();
}

/*------------------------------------------------------------------------
Function Name: SetTransparency
Description:
   This function sets whether the bitmap displayed in this control will
   be drawn with a transparent color
Parameters: bool transparent - true if the transparent color is to be
               used in drawing the bitmap, false otherwise
------------------------------------------------------------------------*/

void DGImage::SetTransparency(bool transparent)
{
   transparentBitmap = transparent;

   if(transparentBitmap)
   {
      DGBitmap* bitmap = dgGraphics->GetBitmap(bitmapID);
      if(bitmap != NULL)
         bitmap->SetTransparentColor(transparentColor);
   }   
}

/*------------------------------------------------------------------------
Function Name: SetTransparentColor
Description:
   This function sets which color in the bitmap displayed by this control
   will be transparent. A transparent color is a color which is not drawn
   on the screen.
Parameters: DGColor color - the color in the bitmap to be made 
               transparent
------------------------------------------------------------------------*/

void DGImage::SetTransparentColor(DGColor color)
{
   transparentColor = color;

   if(transparentBitmap)
   {
      DGBitmap* bitmap = dgGraphics->GetBitmap(bitmapID);
      if(bitmap != NULL)
         bitmap->SetTransparentColor(transparentColor);
   }
}

/*------------------------------------------------------------------------
Function Name: SetBitmapOrigin
Description:
   This function changes where the upper-left corner of the bitmap is 
   displayed in the window
Parameters: DGPoint coords - the window coordinates of where the 
               upper-left corner of the bitmap will be drawn
------------------------------------------------------------------------*/

void DGImage::SetBitmapOrigin(DGPoint coords)
{
   bitmapOrigin = coords;
}

/*------------------------------------------------------------------------
Function Name: SetBitmapSize
Description:
   This function returns the size of the bitmap that is being displayed.
Returns: the size of the bitmap being displayed by this control.
   If no bitmap is currently being displayed, then (0, 0) will be 
   returned.
------------------------------------------------------------------------*/

DGPoint DGImage::GetBitmapSize()
{
   DGPoint bitmapSize(0, 0);

   DGBitmap* bitmap = dgGraphics->GetBitmap(bitmapID);
   if(bitmap != NULL)
      bitmapSize = DGPoint(bitmap->GetWidth(), bitmap->GetHeight());

   return bitmapSize;
}

void FC DGImage::OnDrawWindow(DGWindowSurface* surface)
{
   DGBitmap* bitmap = dgGraphics->GetBitmap(bitmapID);

   if(bitmap != NULL)
   {
      if(transparentBitmap)
         surface->DrawTransparentBitmap(bitmapOrigin, bitmapID);
      else
         surface->DrawBitmap(bitmapOrigin, bitmapID);
   }
   else if(!transparentBitmap)
      surface->FillSurface(DGColor(128, 128, 128));
}

void FC DGImage::OnLButtonDown(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_LBUTTONDOWN,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnLButtonUp(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_LBUTTONUP,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnLButtonDblClk(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_LBUTTONDBLCLK,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnMButtonDown(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_MBUTTONDOWN,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnMButtonUp(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_MBUTTONUP,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnMButtonDblClk(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_MBUTTONDBLCLK,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnRButtonDown(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_RBUTTONDOWN,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnRButtonUp(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_RBUTTONUP,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnRButtonDblClk(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_RBUTTONDBLCLK,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnMouseMove(int x, int y, BYTE* keyboardState)
{
   if(parentNotify)
   {
      DGMessage* msg = new DGMessage(GM_IMAGE_MOUSEMOVE,
         GetParent()->GetWindowID(), 0, 0, GetWindowID());

      //Translate the coords back to absolute coords
      DGPoint absoluteCoords = RelToAbsCoords(x, y);
      msg->data1 = absoluteCoords.x;
      msg->data2 = absoluteCoords.y;

      GetParent()->SendMessage(msg);
      delete msg;
   }
}

void FC DGImage::OnWindowSized()
{
   //Set the origin of the bitmap depending on whether it is smaller or
   //larger than the image control
   DGPoint bitmapSize = GetBitmapSize();
   DGPoint windowSize = GetSize();

   if(bitmapSize.x < windowSize.x)
      bitmapOrigin.x = (windowSize.x - bitmapSize.x) / 2;
   else
      bitmapOrigin.x = bitmapOrigin.x;

   if(bitmapSize.y < windowSize.y)
      bitmapOrigin.y = (windowSize.y - bitmapSize.y) / 2;
   else
      bitmapOrigin.y = bitmapOrigin.y;
}
