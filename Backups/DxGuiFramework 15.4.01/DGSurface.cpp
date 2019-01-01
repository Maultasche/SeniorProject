/*------------------------------------------------------------------------
File Name: DGSurface.cpp
Description: This file contains the implementation of the DGSurface class, 
	which represents an area of the screen that can be drawn upon.
Version:
   1.0.0    24.03.2000  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

/*Constructor*/
//rect.right and rect.bottom are the width and height of the surface.
DGSurface::DGSurface(DGArea& area)
{
#ifdef _DEBUG
   DGPoint res = dgGraphics->GetResolution();
//   assert(area.left >= 0 && area.left < res.x && 
//      area.top >= 0 && area.top < res.y);
#endif

   screenArea = area;
}

/*Destructor*/
DGSurface::~DGSurface()
{

}

//Non-Blit Drawing Functions
void FC DGSurface::SetPixel(int x, int y, DGColor& color)
{
   //Clip to within the surface
   if(x >= 0 && x < screenArea.width && y >= 0 && y < screenArea.height)
   {
      //Clip to within the screen
      int drawX = x + screenArea.left;
      int drawY = y + screenArea.top;

      DGPoint res = dgGraphics->GetResolution();
      if(drawX < res.x && drawY < res.y && drawX >= 0 && drawY >= 0)
         dgGraphics->SetPixel(drawX, drawY, color);
   }
}

void FC DGSurface::DrawHorizontalLine(int x1, int x2, int y, DGColor& color)
{
   //Clip to within the surface
   if((y < screenArea.height && y >= 0) && 
      (x1 < screenArea.width || x2 < screenArea.width) &&
      (x1 >= 0 || x2 >= 0))
   {
      //Make adjustments to keep the line within the surface
      if(x1 < 0)
         x1 = 0;
      else if(x1 >= screenArea.width)
         x1 = screenArea.width - 1;
      if(x2 < 0)
         x2 = 0;
      else
         x2 = screenArea.width - 1;

      //Clip to within the screen
      int drawX1 = x1 + screenArea.left;
      int drawX2 = x2 + screenArea.left;
      int drawY = y + screenArea.top;

      DGPoint res = dgGraphics->GetResolution();

      //Check to see if at least part of the line is within the screen area
      if((drawY < res.y && drawY >= 0) && (drawX1 < res.x || drawX2 < res.x) &&
         (drawX1 >= 0 || drawX2 >= 0))
      {
         //Make adjustments to keep the line within the screen
         if(drawX1 < 0)
            drawX1 = 0;
         else if(drawX1 >= res.x)
            drawX1 = res.x - 1;
         if(drawX2 < 0)
            drawX2 = 0;
         else if(drawX2 >= res.x)
            drawX2 = res.x - 1;
        
         dgGraphics->DrawHorizontalLine(drawX1, drawX2, drawY, color);
      }
   }
}

void FC DGSurface::DrawVerticalLine(int x, int y1, int y2, DGColor& color)
{
   //Clip to within the surface
   if((x < screenArea.width && x >= 0) && 
      (y1 < screenArea.height || y2 < screenArea.height) &&
      (y1 >= 0 || y2 >= 0))
   {
      //Make adjustments to keep the line within the surface
      if(y1 < 0)
         y1 = 0;
      else if(y1 >= screenArea.height)
         y1 = screenArea.height - 1;
      if(y2 < 0)
         y2 = 0;
      else
         y2 = screenArea.height - 1;

      //Clip to within the screen
      int drawY1 = y1 + screenArea.top;
      int drawY2 = y2 + screenArea.top;
      int drawX = x + screenArea.left;

      DGPoint res = dgGraphics->GetResolution();

      //Check to see if at least part of the line is within the screen area
      if((drawX < res.y && drawX >= 0) && (drawY1 < res.y || drawY2 < res.y) &&
         (drawY1 >= 0 || drawY2 >= 0))
      {
         //Make adjustments to keep the line within the screen
         if(drawY1 < 0)
            drawY1 = 0;
         else if(drawY1 >= res.y)
            drawY1 = res.y - 1;
         if(drawY2 < 0)
            drawY2 = 0;
         else if(drawY2 >= res.y)
            drawY2 = res.y - 1;
         
         dgGraphics->DrawVerticalLine(drawX, drawY1, drawY2, color);
      }
   }
}

void FC DGSurface::DrawLine(DGPoint p1, DGPoint p2, DGColor& color)
{
   //Clip to within the surface
   if((p1.x < screenArea.width || p2.x < screenArea.width) &&
      (p1.x >= 0 || p2.x >= 0) && 
      (p1.y < screenArea.height || p2.y < screenArea.height) &&
      (p1.y >= 0 || p2.y >= 0))
   {
      int ratio;
      int edge;

      //Make adjustments to keep the line within the surface
      //Clip on the right and bottom
      if(p1.x >= screenArea.width)
      {
         edge = screenArea.width - 1;   
         ratio = (((edge - p2.x) << 16) / (p1.x - p2.x));
         p1.x = edge;
         p1.y = p2.y + (((p1.y - p2.y) * ratio) >> 16);
      }
      if(p1.y >= screenArea.height)
      {
         edge = screenArea.height - 1;
         ratio = (((edge - p2.y) << 16) / (p1.y - p2.y));
         p1.y = edge;
         p1.x = p2.x + (((p1.x - p2.x) * ratio) >> 16);
      }
      if(p2.x >= screenArea.width)
      {
         edge = screenArea.width - 1;
         ratio = (((edge - p1.x) << 16) / (p2.x - p1.x));
         p2.x = edge;
         p2.y = p1.y + (((p2.y - p1.y) * ratio) >> 16);
      }
      if(p2.y >= screenArea.height)
      {
         edge = screenArea.height - 1;
         ratio = (((edge - p1.y) << 16) / (p2.y - p1.y));
         p2.y = edge;
         p2.x = p1.x + (((p2.x - p1.x) * ratio) >> 16);
      }
      //Clip on the left and top
      if(p1.x < 0)
      {
         ratio = (((-p2.x) << 16) / (p1.x - p2.x));
         p1.x = 0;
         p1.y = p2.y + (((p1.y - p2.y) * ratio) >> 16);
      }
      if(p1.y < 0)
      {
         ratio = (((-p2.y) << 16) / (p1.y - p2.y));
         p1.y = 0;
         p1.x = p2.x + (((p1.x - p2.x) * ratio) >> 16);
      }
      if(p2.x < 0)
      {
         ratio = (((-p1.x) << 16) / (p2.x - p1.x));
         p2.x = 0;
         p2.y = p1.y + (((p2.y - p1.y) * ratio) >> 16);
      }
      if(p2.y < 0)
      {
         ratio = (((-p1.y) << 16) / (p2.y - p1.y));
         p2.y = 0;
         p2.x = p1.x + (((p2.x - p1.x) * ratio) >> 16);
      }

      //Clip to within the screen
      int drawY1 = p1.y + screenArea.top;
      int drawY2 = p2.y + screenArea.top;
      int drawX1 = p1.x + screenArea.left;
      int drawX2 = p2.x + screenArea.left;

      DGPoint res = dgGraphics->GetResolution();

      //Check to see if at least part of the line is within the screen area
      if((drawX1 < res.x || drawX2 < res.x) && (drawX1 >= 0 || drawX2 >= 0) && 
         (drawY1 < res.y || drawY2 < res.y) && (p1.y >= 0 || p2.y >= 0))
      {

         dgGraphics->DrawLine(DGPoint(drawX1, drawY1), DGPoint(drawX2, drawY2), color);
      }
   }
/*
   p1.Offset(screenArea.left, screenArea.top);
   p2.Offset(screenArea.left, screenArea.top);
   dgGraphics->DrawLine(p1, p2, color);*/
}

