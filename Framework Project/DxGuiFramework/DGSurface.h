/*------------------------------------------------------------------------
File Name: DGSurface.h
Description: This file contains the DGSurface class, which represents an 
	area of the screen that can be drawn upon.
Version:
   1.0.0    24.03.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGSURFACE_H
#define DGSURFACE_H

extern DGGraphics* dgGraphics;

class DGSurface
{
public:
   DGSurface(DGArea& area);
   virtual ~DGSurface();

   DGPoint GetSize(void) 
   {return DGPoint(screenArea.width, screenArea.height);}

   void SetWindowOrg(DGPoint origin);
   void RemoveWindowOrg(void);

   //Drawing Functions
   void FC LockSurface(void) {dgGraphics->LockSurface();}
   void FC UnlockSurface(void) {dgGraphics->UnlockSurface();}

   //Non-Blit Drawing Functions
   void FC SetPixel(int x, int y, DGColor& color);
   void FC DrawHorizontalLine(int x1, int x2, int y, DGColor& color);
   void FC DrawVerticalLine(int x, int y1, int y2, DGColor& color);
   void FC DrawLine(DGPoint p1, DGPoint p2, DGColor& color);
   void FC DrawRectangle(DGRectangle rect, DGColor& color);
   void FC DrawFilledRectangle(DGRectangle rect, DGColor& color);

   //Blit Drawing Functions
   void FC FillArea(DGArea area, DGColor& color)
   {
      area.Offset(screenArea.left, screenArea.top);
      dgGraphics->FillArea(area, color);
   } 
   
   void FC FillSurface(DGColor& color) 
   {dgGraphics->FillArea(screenArea, color);}

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

   void FC DrawText(char* text, DGRectangle& rect, UINT flags)
   {
      rect.Offset(screenArea.left, screenArea.top);
      dgGraphics->DrawText(text, rect, flags);

      //If there is DT_CALCRECT flag, translate the result 
      //of the method call.
      if(flags & DT_CALCRECT)
         rect.Offset(-screenArea.left, -screenArea.top);
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
   
   //Stores the origin in surface coordinates of the window that currently
   //being drawn. This is necessary to allow a child window to clip its edge
   //at the edge of its parent window. Otherwise the upper-left corner of the
   //window being drawn would always be at the upper-left corner of the screen
   //surface, which isn't the case when the upper-left portion of the window
   //being drawn is clipped.
   DGPoint* windowOrg;
};

#endif