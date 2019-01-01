/*------------------------------------------------------------------------
File Name: DGSurface.h
Description: This file contains the DGSurface class, which represents an 
	area of the screen that can be drawn upon.
Version:
   1.0.0    24.03.2000  Created the file
------------------------------------------------------------------------*/

#ifndef DGSURFACE_H
#define DGSURFACE_H

extern DGGraphics* dgGraphics;

class DGSurface
{
public:
   DGSurface(DGArea& area);
   virtual ~DGSurface();

   //Drawing Functions
   void FC LockSurface(void) {dgGraphics->LockSurface();}
   void FC UnlockSurface(void) {dgGraphics->UnlockSurface();}

   //Non-Blit Drawing Functions
   void FC SetPixel(int x, int y, DGColor& color)
   {dgGraphics->SetPixel(x + screenArea.left, y + screenArea.top, color);}

   void FC DrawHorizontalLine(int x1, int x2, int y, DGColor& color)
   {dgGraphics->DrawHorizontalLine(x1 + screenArea.left, x2 + screenArea.left,
      y + screenArea.top, color);}

   void FC DrawVerticalLine(int x, int y1, int y2, DGColor& color)
   {dgGraphics->DrawVerticalLine(x + screenArea.left, y1 + screenArea.top,
   y2 + screenArea.top, color);}

   void FC DrawLine(DGPoint p1, DGPoint p2, DGColor& color)
   {
      p1.Offset(screenArea.left, screenArea.top);
      p2.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawLine(p1, p2, color);
   }

   void FC DrawRectangle(DGRectangle rect, DGColor& color)
   {
      rect.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawRectangle(rect, color);
   }

   void FC DrawFilledRectangle(DGRectangle rect, DGColor& color)
   {
      rect.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawFilledRectangle(rect, color);
   }

   //Blit Drawing Functions
   void FC FillArea(DGRectangle rect, DGColor& color)
   {
      rect.Offset(screenArea.left, screenArea.top);
      dgGraphics->FillArea(rect, color);
   } 
   
   void FC FillScreen(DGColor& color) 
   {dgGraphics->FillScreen(color);}

   void FC DrawBitmap(DGPoint location, UINT bitmapID)
   {
      location.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawBitmap(location, bitmapID);
   }

   void FC DrawScaledBitmap(DGArea area, UINT bitmapID)
   {
      area.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawScaledBitmap(area, bitmapID);
   }

   void FC DrawTransparentBitmap(DGPoint location, UINT bitmapID,
      DGColor& transparentColor)
   {
      location.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawTransparentBitmap(location, bitmapID, 
         transparentColor);
   }

   void FC DrawTransparentScaledBitmap(DGArea area, UINT bitmapID,
      DGColor& transparentColor)
   {
      area.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawTransparentScaledBitmap(area, bitmapID,
         transparentColor);
   }

   void FC DrawTransparentBitmap(DGPoint location, UINT bitmapID)
   {
      location.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawTransparentBitmap(location, bitmapID);
   }

   void FC DrawTransparentScaledBitmap(DGArea area, UINT bitmapID)
   {
      area.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawTransparentScaledBitmap(area, bitmapID);
   }

   //GDI Drawing Functions
   void FC SetGDIFont(DGFont& font)
   {dgGraphics->SetGDIFont(font);}

   void FC SetTextTransparency(int mode)
   {dgGraphics->SetTextTransparency(mode);}

   void FC SetTextColor(DGColor& color)
   {dgGraphics->SetTextColor(color);}

   void FC SetTextBackgroundColor(DGColor& color)
   {dgGraphics->SetTextBackgroundColor(color);}

   void FC DrawText(char* text, DGRectangle rect, UINT flags)
   {
      rect.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawText(text, rect, flags);
   }


   //The clipping functions for a DGSurface will be implemented once
   //DGGraphics is capable of doing multiple clipping areas.

   //Clipping Functions
   //void FC AddClippingArea(DGRectangle& area);
   //void FC RemoveClippingArea(void);
   //void FC ClearClippingAreas(void);

protected:
   //Stores the area on the screen that the surface represents,
   //surfaceArea.left and surfaceArea.top describe upper-left corner of 
   //the surface, surfaceArea.right and surfaceArea.bottom describe the
   //width and height of the surface
   DGArea screenArea;
};

#endif