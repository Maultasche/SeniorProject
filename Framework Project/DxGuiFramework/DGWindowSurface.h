/*------------------------------------------------------------------------
File Name: DGWindowSurface.h
Description: This file contains the DGWindowSurface class, which 
	represents the area of a window.
Version:
   1.0.0    12.08.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGWINDOWSURFACE_H
#define DGWINDOWSURFACE_H

class DGWindowSurface
{
public:

   /*------------------------------------------------------------------------
   Function Name: Constructor
   Parameters:
      DGSurface* surface : the area on the screen to which the window is to 
         be clipped
      DGPoint winOrigin: the surface coordinates of the upper-left corner 
         of the window
   Description:
      This function constructs the DGWindowSurface object. If winOrigin is
      (0, 0), then the upper-left corner of the window is the same as the
      upper-left corner of the screen surface. If winOrigin coordinates are
      negative then, some of the top and left parts of the window will be
      clipped.
   ------------------------------------------------------------------------*/

   DGWindowSurface(DGSurface* surface, DGPoint winOrigin)
   {
      screenSurface = surface;
      windowOrigin = winOrigin;
   }

   DGPoint GetWindowOrigin(void) {return windowOrigin;}
   void SetWindowOrigin(DGPoint origin) {windowOrigin = origin;}

   DGSurface* GetScreenSurface(void) {return screenSurface;}
   void SetScreenSurface(DGSurface* surface) {screenSurface = surface;}

   //Drawing Functions
   void FC LockSurface(void) {screenSurface->LockSurface();}
   void FC UnlockSurface(void) {screenSurface->UnlockSurface();}

   //Non-Blit Drawing Functions
   void FC SetPixel(int x, int y, DGColor& color)
   {
      screenSurface->SetPixel(x + windowOrigin.x, y + windowOrigin.y, color);
   }

   void FC DrawHorizontalLine(int x1, int x2, int y, DGColor& color)
   {
      screenSurface->DrawHorizontalLine(x1 + windowOrigin.x, x2 + windowOrigin.x,
      y + windowOrigin.y, color);
   }

   void FC DrawVerticalLine(int x, int y1, int y2, DGColor& color)
   {
      screenSurface->DrawVerticalLine(x + windowOrigin.x, y1 + windowOrigin.y,
      y2 + windowOrigin.y, color);
   }

   void FC DrawLine(DGPoint p1, DGPoint p2, DGColor& color)
   {
      p1.Offset(windowOrigin.x, windowOrigin.y);
      p2.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawLine(p1, p2, color);
   }

   void FC DrawRectangle(DGRectangle rect, DGColor& color)
   {
      rect.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawRectangle(rect, color);
   }

   void FC DrawFilledRectangle(DGRectangle rect, DGColor& color)
   {
      rect.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawRectangle(rect, color);
   }

   //Blit Drawing Functions
   void FC FillArea(DGArea area, DGColor& color)
   {
      area.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->FillArea(area, color);
   } 
   
   void FC FillSurface(DGColor& color) 
   {
      screenSurface->FillSurface(color);
   }

   void FC DrawBitmap(DGPoint location, UINT bitmapID)
   {
      location.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawBitmap(location, bitmapID);
   }

   void FC DrawScaledBitmap(DGArea area, UINT bitmapID)
   {
      area.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawScaledBitmap(area, bitmapID);
   }

   void FC DrawTransparentBitmap(DGPoint location, UINT bitmapID,
      DGColor& transparentColor)
   {
      location.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawTransparentBitmap(location, bitmapID, 
         transparentColor);
   }

   void FC DrawTransparentScaledBitmap(DGArea area, UINT bitmapID,
      DGColor& transparentColor)
   {
      area.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawTransparentScaledBitmap(area, bitmapID,
         transparentColor);
   }

   void FC DrawTransparentBitmap(DGPoint location, UINT bitmapID)
   {
      location.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawTransparentBitmap(location, bitmapID);
   }

   void FC DrawTransparentScaledBitmap(DGArea area, UINT bitmapID)
   {
      area.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawTransparentScaledBitmap(area, bitmapID);
   }

   //GDI Drawing Functions
   void FC SetGDIFont(DGFont& font)
   {screenSurface->SetGDIFont(font);}

   void FC SetTextTransparency(int mode)
   {screenSurface->SetTextTransparency(mode);}

   void FC SetTextColor(DGColor& color)
   {screenSurface->SetTextColor(color);}

   void FC SetTextBackgroundColor(DGColor& color)
   {screenSurface->SetTextBackgroundColor(color);}

   void FC DrawText(char* text, DGRectangle& rect, UINT flags)
   {
      rect.Offset(windowOrigin.x, windowOrigin.y);
      screenSurface->DrawText(text, rect, flags);

      //If there is DT_CALCRECT flag, translate the result 
      //of the method call.
      if(flags & DT_CALCRECT)
         rect.Offset(-windowOrigin.x, -windowOrigin.y);
   }

protected:
   DGSurface* screenSurface;
   
   DGPoint windowOrigin;
};

#endif