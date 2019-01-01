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
   assert(area.left >= 0 && area.left < res.x && 
      area.top >= 0 && area.top < res.y);
#endif

   screenArea = area;
}

/*Destructor*/
DGSurface::~DGSurface()
{

}