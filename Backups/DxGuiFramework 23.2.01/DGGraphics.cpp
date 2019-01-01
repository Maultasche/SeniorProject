/*------------------------------------------------------------------------
File Name: DGGraphics.h
Description: This file contains the DGGraphics class implementation, 
   which manages the DirectDraw surfaces and controls and what is drawn 
   to the screen.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

//The callback function used to enumerate the supported display modes.
//Unfortunately it cannot be a member function of any class.
HRESULT CALLBACK EnumDisplayModes(LPDDSURFACEDESC2 lpDDSurfaceDesc,  
   LPVOID lpContext);

DGGraphics::DGGraphics()
{
   OutputDebugString("DGGraphics constructor\n");

   if(instance != NULL)
      return;
   
   instance = this;

   hWnd = DGGetApp()->GetWindowsHandle();
   lpDDSPrimary = NULL;
   lpDDSSecondary = NULL;
   lpDDSDrawingSurface = NULL;
   lpPSClipper = NULL;
   lpSSClipper = NULL;

   surfaceLocked = false;
   SSPersistence = false;

   //Initialize DirectDraw object
   HRESULT result = DirectDrawCreateEx(NULL, (void**)&lpDD, 
      IID_IDirectDraw7, NULL);
   
   if(result != DD_OK)
      HandleDDrawError(EC_DDINIT, result, __FILE__, __LINE__);

   //Get the supported display modes
   result = lpDD->EnumDisplayModes(0, NULL, NULL, 
      (LPDDENUMMODESCALLBACK2)EnumDisplayModes);

   if(result != DD_OK)
      HandleDDrawError(EC_DDINIT, result, __FILE__, __LINE__);

   //Get the hardware capabilities
   ddCaps.dwSize = sizeof(DDCAPS);

   result = lpDD->GetCaps(&ddCaps, NULL);

   if(result != DD_OK)
      HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);
}

DGGraphics::~DGGraphics()
{
   OutputDebugString("DGGraphics destructor\n");

   //Release DirectDraw object
   if(lpDD != NULL)
   {
      lpDD->Release();
      lpDD = NULL;
   }

   DestroyAllSurfaces();
}

void DGGraphics::SetResolution(DGPoint res)
{
   SetGraphicsMode(res, windowedState, colorDepth, bufferingMode,
      SSPersistence);
}

void DGGraphics::SetResolution(int hRes, int vRes)
{
   SetGraphicsMode(DGPoint(hRes, vRes), windowedState, colorDepth, 
      bufferingMode, SSPersistence);
}

void DGGraphics::SetWindowedState(UINT winState)
{
   SetGraphicsMode(screenRes, winState, colorDepth, bufferingMode,
      SSPersistence);
}

void DGGraphics::SetColorDepth(UINT clrDepth)
{
   SetGraphicsMode(screenRes, windowedState, clrDepth, bufferingMode,
      SSPersistence);
}

UINT DGGraphics::GetColorDepth(void)
{
   //return CD_16BIT, not the specialized modes
   if(colorDepth == CD_16BIT5 || colorDepth == CD_16BIT6)
      return CD_16BIT;
   else
      return colorDepth;
}


void DGGraphics::SetBufferingMode(UINT bufferMode)
{
   SetGraphicsMode(screenRes, windowedState, colorDepth, bufferMode,
      SSPersistence);
}

void DGGraphics::SetSurfacePersistence(bool persistence)
{
   SetGraphicsMode(screenRes, windowedState, colorDepth, bufferingMode,
      persistence);
}

void DGGraphics::SetGraphicsMode(DGPoint res, UINT winState, UINT clrDepth,
      UINT bufferMode, bool persistence)
{
   //Change things so that when an exception is thrown, no member variables
   //are permanently altered.

   HRESULT result;

   DestroyAllSurfaces();

   //If we want windowed mode
   if(winState == WS_WINDOWED)
   {
      HWND desktopWindow;
      int desktopClrDepth;

      //Set the cooperative level.
      result = lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      //If we are switching to windowed mode, we need to question the desktop
      //about its color depth

      desktopWindow = GetDesktopWindow();
      HDC desktopDC = GetDC(desktopWindow);
      desktopClrDepth = GetDeviceCaps(desktopDC, BITSPIXEL);
      ReleaseDC(desktopWindow, desktopDC);
      
      //Check to see if MS Windows is at a sufficient color depth
      if(desktopClrDepth != 16 && desktopClrDepth != 24 && 
         desktopClrDepth != 32)
      {
         throw new DGException("Only 16-, 24-, and 32-bit color depths are "\
            "supported. Windows needs to be set to 16-bit or true color.", 
            EC_DDSETGRAPHMODE, ET_DIRECTDRAW, __FILE__, __LINE__);
      }

      result = lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      //Change the window so that it has a title and borders and is centered
      //on the screen
      SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
      
      //Calculate the size of the window when the client area represents the
      //application resolution
      int xWindowSize = res.x + (GetSystemMetrics(SM_CXSIZEFRAME) * 2);
      int yWindowSize = res.y + (GetSystemMetrics(SM_CYSIZEFRAME) * 2) +
         GetSystemMetrics(SM_CYSIZE);

      //If the size is the same as the Windows resolution, the window will
      //automatically be full-screen.

      SetWindowPos(hWnd, 0, 
         (GetSystemMetrics(SM_CXSCREEN) - res.x) / 2,
         (GetSystemMetrics(SM_CYSCREEN) - res.y) / 2,
         xWindowSize, yWindowSize, SWP_SHOWWINDOW);

      //Prepare to create the primary surface
      memset(&ddsd, 0, sizeof(ddsd));
      ddsd.dwSize = sizeof(ddsd); 

      ddsd.dwFlags = DDSD_CAPS;
      ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; 
 
      //Create the primary surface
      result = lpDD->CreateSurface(&ddsd, &lpDDSPrimary, NULL);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      //Set up a clipper on the primary surface so that we don't draw all over
      //the rest of the screen.
      result = lpDD->CreateClipper(0, &lpPSClipper, NULL);
   
      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      result = lpPSClipper->SetHWnd(0, hWnd);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      result = lpDDSPrimary->SetClipper(lpPSClipper);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      //lpPSClipper->Release();

      //Create the windowed secondary surface, which is actually an offscreen
      //surface.  This takes place no matter what the buffering mode is.
      //Triple buffering has no effect in windowed mode, and single buffering
      //require complicated complications to draw in a window.
      ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; 
      ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN; 
      ddsd.dwHeight = res.y; 
      ddsd.dwWidth = res.x; 
      result = lpDD->CreateSurface(&ddsd, &lpDDSSecondary, NULL); 

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);
      
      lpDDSDrawingSurface = lpDDSSecondary;

      ClearPrimarySurface();
      FillScreen(DGColor(0, 0, 0));

      colorDepth = desktopClrDepth;

      switch(desktopClrDepth)
      {
         case 16:
            colorDepth = CD_16BIT;
            bytesPerPixel = 2;
            break;
         case 24:
            colorDepth = CD_24BIT;
            bytesPerPixel = 3;
            break;
         case 32:
            colorDepth = CD_32BIT;
            bytesPerPixel = 4;
            break;
      }
   }

   //We want full-screen mode
   else
   {
      //First check to see if the desired mode is supported
      if(clrDepth != CD_16BIT && clrDepth != CD_24BIT && clrDepth != CD_32BIT)
      {
         throw new DGException("Only 16-, 24-, and 32-bit color depths are "\
            "supported.", EC_DDSETGRAPHMODE, ET_DIRECTDRAW, __FILE__, __LINE__);
      }

      SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

      result = lpDD->SetCooperativeLevel(hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE |
         DDSCL_FULLSCREEN);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      //We need to change the color depth flag to a number
      int clrBitNum = 0;

      switch(clrDepth)
      {
         case CD_16BIT:
            clrBitNum = 16;
            bytesPerPixel = 2;
            break;
         //Usually video cards will support only 32-bit modes, but a minority
         //support only 24-bit. The colors are the same in both modes, so we
         //can choose which one is best.
         case CD_24BIT:
         case CD_32BIT:
            if(displayModeList.DisplayModeSupported(res.x, res.y, 24))
            {
               clrBitNum = 24;
               bytesPerPixel = 3;
            }
            else
            {
               clrBitNum = 32;
               bytesPerPixel = 4;
            }
         break;
         default: break;
      }

      //Set the display mode
      result = lpDD->SetDisplayMode(res.x, res.y, clrBitNum, 0, 0);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

      //Prepare to create the primary surface
      memset(&ddsd, 0, sizeof(ddsd));
      ddsd.dwSize = sizeof(ddsd); 
         
      if(bufferMode == BT_SINGLE || persistence == true)
      {
            OutputDebugString("Persistence == true\n");
            ddsd.dwFlags = DDSD_CAPS;
            ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; 
      }
      
      else if(bufferMode == BT_DOUBLE)
      {
         ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT; 
         ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | 
         DDSCAPS_FLIP | DDSCAPS_COMPLEX; 
         ddsd.dwBackBufferCount = 1;
      }
      
      else if(bufferMode == BT_TRIPLE)
      {
         ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT; 
         ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | 
            DDSCAPS_FLIP | DDSCAPS_COMPLEX; 
         ddsd.dwBackBufferCount = 2;
      }

      else
         throw new DGException("The buffer mode flag is not valid", 
            EC_DDSETGRAPHMODE, ET_DIRECTDRAW, __FILE__, __LINE__);

      //Create the primary surface
      result = lpDD->CreateSurface(&ddsd, &lpDDSPrimary, NULL);

      if(result != DD_OK)
         HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);
      
      if(bufferMode != BT_SINGLE)
      {
         if(persistence)
         {
            ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; 
            ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN; 
            ddsd.dwHeight = res.y; 
            ddsd.dwWidth = res.x; 
            result = lpDD->CreateSurface(&ddsd, &lpDDSSecondary, NULL); 
         }

         else
         {
            DDSCAPS2 ddsCaps;
            memset(&ddsCaps, 0, sizeof(ddsCaps));
            ddsCaps.dwCaps = DDSCAPS_BACKBUFFER; 
            result = lpDDSPrimary->GetAttachedSurface(&ddsCaps, &lpDDSSecondary); 
         }

         if(result != DD_OK)
            HandleDDrawError(EC_DDSETGRAPHMODE, result, __FILE__, __LINE__);

         lpDDSDrawingSurface = lpDDSSecondary;
      }

      else
         lpDDSDrawingSurface = lpDDSPrimary;   

      colorDepth = clrDepth;
   }

   //If the color depth is 16-bit, we need to find out what type of 16-bit
   //pixel format the video card used (6 bits for green or 5 bits for green).
   if(colorDepth == CD_16BIT)
   {
      //Test the primary surface
      ddsd.dwSize = sizeof(ddsd);
      lpDDSPrimary->GetSurfaceDesc(&ddsd);
      //If 5 bits are being used for green
      if(ddsd.ddpfPixelFormat.dwGBitMask == 0x3E0)
         colorDepth = CD_16BIT5;
      //If 6 bits are being used for green
      else
         colorDepth = CD_16BIT6;
   }

   bufferingMode = bufferMode;

   screenRes.x = res.x;
   screenRes.y = res.y;

   windowedState = winState;
 
   if(bufferingMode == BT_SINGLE)
      SSPersistence = false;
   else
      SSPersistence = persistence;
}

void DGGraphics::BeginFrame()
{
   if(bufferingMode != BT_SINGLE && SSPersistence == false)
   {
      DDBLTFX bltFx;
      bltFx.dwSize = sizeof(bltFx);
      bltFx.dwFillColor = 0;
      lpDDSSecondary->Blt(NULL, NULL, NULL, 
         DDBLT_COLORFILL | DDBLT_WAIT, &bltFx);
   }
}

void DGGraphics::EndFrame()
{
   FlipSurface();
}

//Drawing Functions
void FC DGGraphics::LockSurface(void)
{
   assert(surfaceLocked == false);

   HRESULT result;

   memset(&ddsd, 0, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd);
   
   result = lpDDSDrawingSurface->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR |
      DDLOCK_WAIT, NULL);

   switch(result)
   {
      case DDERR_SURFACELOST:
         RestoreAllSurfaces();
         LockSurface();
         break;
      case DD_OK:
         HandleDDrawError(EC_DDLOCKSURFACE, result, __FILE__, __LINE__);
         videoBuffer = (UCHAR*)ddsd.lpSurface;
         bufferPitch = ddsd.lPitch;
         surfaceLocked = true;
         break;
   }
   
#ifdef _DEBUG
   lpDDSDrawingSurface->Unlock(NULL);
#endif
}

void FC DGGraphics::UnlockSurface(void)
{
   assert(surfaceLocked == true);

#ifndef _DEBUG
   HRESULT result;

   result = lpDDSDrawingSurface->Unlock(NULL);

   if(result != DD_OK)
      HandleDDrawError(EC_DDLOCKSURFACE, result, __FILE__, __LINE__);
#endif

   videoBuffer = NULL;
   surfaceLocked = false;
}

void FC DGGraphics::FlipSurface(void)
{
   HRESULT result;

   if(IsIconic(hWnd))
      return;

   if(surfaceLocked)
      UnlockSurface();

   //Check to see if the DirectDraw surfaces were lost
   if(lpDDSPrimary->IsLost() == DDERR_SURFACELOST)
      RestoreAllSurfaces();

   //If we are in windowed mode
   if(windowedState == WS_WINDOWED)
   {
      result = lpDDSPrimary->Blt(&clientRect, lpDDSSecondary, NULL, 
         DDBLT_WAIT, 0);
   }

   //If we are in full-screen single buffer mode, no flipping required
   else if(bufferingMode == BT_SINGLE)
   {
      return;
   }

   //If we are in full-screen mode with a persistent secondary surface
   else if(SSPersistence)
   {
      result = lpDDSPrimary->Blt(NULL, lpDDSSecondary, NULL, DDBLT_WAIT, 0);
   }

   //If we are in full-screen mode with normal flipping
   else
   {
      result = lpDDSPrimary->Flip(NULL, DDFLIP_WAIT);
   }

   if(result != DD_OK)
      HandleDDrawError(EC_DDFLIPSURFACE, result, __FILE__, __LINE__);

}

//Non-Blit Drawing Functions
void FC DGGraphics::SetPixel(int x, int y, DGColor& color)
{
   assert(surfaceLocked == true);
   assert(x >= 0 && x < screenRes.x && y >= 0 && y < screenRes.y);

   switch(colorDepth)
   {
      case CD_16BIT5:
         ((USHORT*)videoBuffer)[x + y * (bufferPitch >> 1)] = color.To16Bit5();
         break;
      case CD_16BIT6:
         ((USHORT*)videoBuffer)[x + y * (bufferPitch >> 1)] = color.To16Bit6();
         break;
      case CD_24BIT:
         videoBuffer[(x * 3) + (y * bufferPitch)] = color.r;
         videoBuffer[(x * 3) + (y * bufferPitch) + 1] = color.g;
         videoBuffer[(x * 3) + (y * bufferPitch) + 2] = color.b;
         break;
      case CD_32BIT:
         ((UINT*)videoBuffer)[x + y * (bufferPitch >> 2)] = color.To32Bit();
         break;
   }
}

void FC DGGraphics::DrawHorizontalLine(int x1, int x2, int y, DGColor& color)
{
   assert(surfaceLocked == true);
   assert(x1 >= 0 && x1 < screenRes.x && x2 >= 0 && x2 < screenRes.x &&
      y >= 0 && y < screenRes.y);

   int beginX, endX;
   if(x1 < x2)
   {
      beginX = x1;
      endX = x2;
   }
   else
   {
      beginX = x2;
      endX = x1;
   }

   int bufferPosition;
   switch(colorDepth)
   {
      case CD_16BIT5:
      case CD_16BIT6:
         bufferPosition = beginX + y * (bufferPitch >> 1);
         break;
      case CD_24BIT:
         bufferPosition = (beginX * 3) + (y * bufferPitch);
         break;
      case CD_32BIT:
         bufferPosition = beginX + y * (bufferPitch >> 2);
         break;
   }

   for(int x = beginX; x <= endX; x++)
   {
      switch(colorDepth)
      {
         case CD_16BIT5:
            ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit5();
            bufferPosition++;
            break;
         case CD_16BIT6:
            ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit6();
            bufferPosition++;
            break;
         case CD_24BIT:
            videoBuffer[bufferPosition] = color.r;
            videoBuffer[bufferPosition + 1] = color.g;
            videoBuffer[bufferPosition + 2] = color.b;
            bufferPosition = bufferPosition + 3;
            break;
         case CD_32BIT:
            ((UINT*)videoBuffer)[bufferPosition] = color.To32Bit();
            bufferPosition++;
            break;
      }      
   }
}

void FC DGGraphics::DrawVerticalLine(int x, int y1, int y2, DGColor& color)
{
   assert(surfaceLocked == true);
   assert(x >= 0 && x < screenRes.x && y1 >= 0 && y1 < screenRes.y &&
      y2 >= 0 && y2 < screenRes.y);

   int beginY, endY;
   if(y1 < y2)
   {
      beginY = y1;
      endY = y2;
   }
   else
   {
      beginY = y2;
      endY = y1;
   }

   int bufferPosition;
   switch(colorDepth)
   {
      case CD_16BIT5:
      case CD_16BIT6:
         bufferPosition = x + beginY * (bufferPitch >> 1);
         break;
      case CD_24BIT:
         bufferPosition = (x * 3) + (beginY * bufferPitch);
         break;
      case CD_32BIT:
         bufferPosition = x + beginY * (bufferPitch >> 2);
         break;
   }

   for(int y = beginY; y <= endY; y++)
   {
      switch(colorDepth)
      {
         case CD_16BIT5:
            ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit5();
            bufferPosition = bufferPosition + (bufferPitch >> 1);
            break;
         case CD_16BIT6:
            ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit6();
            bufferPosition = bufferPosition + (bufferPitch >> 1);
            break;
         case CD_24BIT:
            videoBuffer[bufferPosition] = color.r;
            videoBuffer[bufferPosition + 1] = color.g;
            videoBuffer[bufferPosition + 2] = color.b;
            bufferPosition = (bufferPosition + bufferPitch) - 3;
            break;
         case CD_32BIT:
            ((UINT*)videoBuffer)[bufferPosition] = color.To32Bit();
            bufferPosition = bufferPosition + (bufferPitch >> 2);
            break;
      }      
   }
}

void FC DGGraphics::DrawLine(DGPoint& p1, DGPoint& p2, DGColor& color)
{
   assert(surfaceLocked == true);
   assert(p1.x >= 0 && p1.x < screenRes.x && p1.y >= 0 && p1.y < screenRes.y);
   assert(p2.x >= 0 && p2.x < screenRes.x && p2.y >= 0 && p2.y < screenRes.y);

   //Difference along the x axis
   int dx = p2.x - p1.x;

   //Difference along the y axis
   int dy = p2.y - p1.y;
   
   //Increment to get to the next pixel in the x direction
   int xInc;
   
   //Increment to get to the next pixel in the y direction
   int yInc;

   //The error factor which tells us when to move to the next pixel line/column
   int errorFactor = 0;

   //The position in the buffer
   int bufferPosition;

   switch(colorDepth)
   {
      case CD_16BIT5:
      case CD_16BIT6:
         bufferPosition = p1.x + p1.y * (bufferPitch >> 1);
         break;
      case CD_24BIT:
         bufferPosition = (p1.x * 3) + (p1.y * bufferPitch);
         break;
      case CD_32BIT:
         bufferPosition = p1.x + p1.y * (bufferPitch >> 2);
         break;
   }

   //Now we need to calculate in which direction we need to go when
   //drawing the line

   //Line is moving to the right
   if(dx >= 0)
   {
      switch(colorDepth)
      {
         case CD_16BIT5:
         case CD_16BIT6:
         case CD_32BIT:
            xInc = 1;
            break;
         case CD_24BIT:
            xInc = 3;
            break;         
      }
   }
   //Line is moving to the left
   else
   {
      switch(colorDepth)
      {
         case CD_16BIT5:
         case CD_16BIT6:
         case CD_32BIT:
            xInc = -1;
            break;
         case CD_24BIT:
            xInc = -3;
            break;         
      }
      dx = -dx;
   }

   //Line is moving down
   if(dy >= 0)
   {
      switch(colorDepth)
      {
         case CD_16BIT5:
         case CD_16BIT6:
            yInc = bufferPitch >> 1;
            break;
         case CD_24BIT:
            yInc = bufferPitch;
            break;         
         case CD_32BIT:
            yInc = bufferPitch >> 2;
      }
   }

   //Line is moving up
   else
   {
      switch(colorDepth)
      {
         case CD_16BIT5:
         case CD_16BIT6:
            yInc = -(bufferPitch >> 1);
            break;
         case CD_24BIT:
            yInc = -bufferPitch;
            break;         
         case CD_32BIT:
            yInc = -(bufferPitch >> 2);
      }
      dy = -dy;
   }


   //Now we draw the line
   if(dx > dy)
   {
      for(int i = 0; i <= dx; i++)
      {
         //Set the pixel
         switch(colorDepth)
         {  
            case CD_16BIT5:
               ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit5();
               break;
            case CD_16BIT6:
               ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit6();
               break;
            case CD_24BIT:
               videoBuffer[bufferPosition] = color.r;
               videoBuffer[bufferPosition + 1] = color.g;
               videoBuffer[bufferPosition + 2] = color.b;
               break;
            case CD_32BIT:
               ((UINT*)videoBuffer)[bufferPosition] = color.To32Bit();
               break;   
         }

         //Adjust the error factor
         errorFactor = errorFactor + dy;

         //Test to see if error has overflowed
         if(errorFactor > dx)
         {
            errorFactor = errorFactor - dx;

            //Move to next line
            bufferPosition = bufferPosition + yInc;
      	}

         //Move to the next pixel
         bufferPosition = bufferPosition + xInc;
      }
   }

   else
   {
      for (int i = 0; i <= dy; i++)
      {
         //Set the pixel
         switch(colorDepth)
         {  
            case CD_16BIT5:
               ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit5();
               break;
            case CD_16BIT6:
               ((USHORT*)videoBuffer)[bufferPosition] = color.To16Bit6();
               break;
            case CD_24BIT:
               videoBuffer[bufferPosition] = color.r;
               videoBuffer[bufferPosition + 1] = color.g;
               videoBuffer[bufferPosition + 2] = color.b;
               break;
            case CD_32BIT:
               ((UINT*)videoBuffer)[bufferPosition] = color.To32Bit();
               break;   
         }

         //Adjust the error factor
         errorFactor = errorFactor + dx;

         //Test to see if error overflowed
         if(errorFactor > 0)
         {
            errorFactor = errorFactor - dy;

            //Move to next line
            bufferPosition = bufferPosition + xInc;

         }

         //Move to the next pixel
         bufferPosition = bufferPosition + yInc;
      }
   }
}

void FC DGGraphics::DrawRectangleBorder(DGRectangle& rect, DGColor& color)
{

}

void FC DGGraphics::DrawRect(DGRectangle& rect, DGColor& color)
{

}

//Blit Drawing Functions
void FC DGGraphics::FillScreen(DGColor& color)
{
   HRESULT result;

   DDBLTFX bltFx;
   bltFx.dwSize = sizeof(bltFx);
   
   switch(colorDepth)
   {
      case CD_16BIT5:
         bltFx.dwFillColor = color.To16Bit5();
         break;
      case CD_16BIT6:
         bltFx.dwFillColor = color.To16Bit6();
         break;
      default:
         bltFx.dwFillColor = color.To32Bit();
         break;
   }

   result = lpDDSDrawingSurface->Blt(NULL, NULL, NULL, 
      DDBLT_COLORFILL | DDBLT_WAIT, &bltFx);

   if(result != DD_OK)
      HandleDDrawError(EC_DDFILLSCREEN, result, __FILE__, __LINE__);
}

//Private Functions
void FC DGGraphics::RestoreAllSurfaces()
{
   HRESULT result;

   //Try to restore the primary surface
   result = lpDDSPrimary->Restore();

   //Check to see if the display mode has been changed
   if(result == DDERR_WRONGMODE)
   {
      SetGraphicsMode(screenRes, windowedState, colorDepth, 
         bufferingMode, SSPersistence);
      
      result = lpDDSPrimary->Restore();
   }

   if(result != DD_OK)
      HandleDDrawError(EC_DDRESTORESURFACES, result, __FILE__, __LINE__);

   //Reload the bitmaps
}

void FC DGGraphics::DestroyAllSurfaces()
{
   //Get rid of the old surfaces
   if(lpDDSPrimary != NULL)
   {
      lpDDSPrimary->Release();
      lpDDSPrimary = NULL;
   }

   //Don't release the secondary surface when it is part of
   //a flipping chain.
   if(lpDDSSecondary != NULL && SSPersistence == true)
   {
      lpDDSSecondary->Release();
      lpDDSSecondary = NULL;
   }

   else
      lpDDSSecondary = NULL;

   //Get rid of old clip lists
   if(lpPSClipper != NULL)
   {
      lpPSClipper->Release();
      lpPSClipper = NULL;
   }

   if(lpSSClipper != NULL)
   {
      lpSSClipper->Release();
      lpSSClipper = NULL;
   }
}

void FC DGGraphics::ClearPrimarySurface()
{
   HRESULT result;

   DDBLTFX bltFx;
   bltFx.dwSize = sizeof(bltFx);
   bltFx.dwFillColor = 0; 

   result = lpDDSDrawingSurface->Blt(NULL, NULL, NULL, 
      DDBLT_COLORFILL | DDBLT_WAIT, &bltFx);

   if(result != DD_OK)
      HandleDDrawError(EC_DDCLEARPRIMARY, result, __FILE__, __LINE__);
}

void DGGraphics::HandleDDrawError(UINT errorCode, HRESULT error, 
   char* fileName, UINT lineNumber)
{
   if(error == DD_OK)
      return;

   char errorText[512];

   switch(error)
   {
      case DDERR_ALREADYINITIALIZED:
         strcpy(errorText, "DirectDraw object has already been initialized.");
         break;
      case DDERR_BLTFASTCANTCLIP:
         strcpy(errorText, "BltFast() cannot be used with a surface "\
            "that has a DirectDrawClipper object attached.");
         break;
      case DDERR_CANNOTATTACHSURFACE: 
         strcpy(errorText, "The surface cannot be attached.");
         break;
      case DDERR_CANNOTDETACHSURFACE: 
         strcpy(errorText, "The surface cannot be detached.");
         break;
      case DDERR_CANTCREATEDC: 
         strcpy(errorText, "The Windows device context could not be "\
            "created.");
         break;
      case DDERR_CANTDUPLICATE:
         strcpy(errorText, "This surface cannot be duplicated.");
         break;
      case DDERR_CANTLOCKSURFACE:
         strcpy(errorText, "The surface cannot be locked.");
         break;
      case DDERR_CANTPAGELOCK: 
         strcpy(errorText, "Page lock failed.");
         break;
      case DDERR_CANTPAGEUNLOCK:
         strcpy(errorText, "Page unlock failed.");
         break;
      case DDERR_CLIPPERISUSINGHWND:
         strcpy(errorText, "The clip list could not be added, as the "\
            "DirectDrawClipper object is already monitoring a window "\
            "handle.");
         break;
      case DDERR_COLORKEYNOTSET: 
         strcpy(errorText, "No source color key has been set");
         break;
      case DDERR_CURRENTLYNOTAVAIL: 
         strcpy(errorText, "No support is currently available for this "\
            "operation");
         break;
      case DDERR_DDSCAPSCOMPLEXREQUIRED: 
         strcpy(errorText, "This surface needs to be a complex surface");
         break;
      case DDERR_DCALREADYCREATED:
         strcpy(errorText, "A device context has already been created for "\
            "this surface");
         break;
      case DDERR_DEVICEDOESNTOWNSURFACE:
         strcpy(errorText, "This surface is owned by another DirectDraw device "\
            "and cannot be used");
         break;
      case DDERR_DIRECTDRAWALREADYCREATED:
         strcpy(errorText, "A DirectDraw object representing this driver has "\
            "already been created.");
         break;
      case DDERR_EXCEPTION:
         strcpy(errorText, "An exception was encountered while performing "\
            "the requested operation.");
         break;
     case DDERR_EXCLUSIVEMODEALREADYSET:
         strcpy(errorText, "Exclusive mode has already been set.");
         break;
      case DDERR_EXPIRED:
         strcpy(errorText, "The data has expired and is invalid.");
         break;
      case DDERR_GENERIC: 
         strcpy(errorText, "An undefined error condition has occurred.");
         break;
      case DDERR_HEIGHTALIGN: 
         strcpy(errorText, "The height of the provided rectangle is not a "\
            "multiple of the required alignment.");
         break;
      case DDERR_HWNDALREADYSET:
         strcpy(errorText, "The cooperative-level window handle has already been "\
            "set.");
         break;
      case DDERR_HWNDSUBCLASSED:
         strcpy(errorText, "DirectDraw cannot restore because the DirectDraw "\
            "cooperative-level window handle has been subclassed.");
         break;
      case DDERR_IMPLICITLYCREATED:
         strcpy(errorText, "Surface cannot be restored because it was implicitly "\
            "created");
         break;
      case DDERR_INCOMPATIBLEPRIMARY:
         strcpy(errorText, "The primary surface creation request does not match "\
            "the existing primary surface.");
         break;
      case DDERR_INVALIDCAPS: 
         strcpy(errorText, "One or more of the capability bits passed to the "\
            "callback function are incorrect.");
         break;
      case DDERR_INVALIDCLIPLIST:
         strcpy(errorText, "DirectDraw does not support the provided clip list.");
         break;
      case DDERR_INVALIDDIRECTDRAWGUID: 
         strcpy(errorText, "The provided GUID is an invalid DirectDraw GUID");
         break;
      case DDERR_INVALIDMODE:
         strcpy(errorText, "DirectDraw does not support the requested mode.");
         break;
      case DDERR_INVALIDOBJECT:
         strcpy(errorText, "DirectDraw received a pointer to an invalid object.");
         break;
      case DDERR_INVALIDPARAMS: 
         strcpy(errorText, "One or more parameters passed to this method are "\
            "incorrect.");
         break;
      case DDERR_INVALIDPIXELFORMAT: 
         strcpy(errorText, "The specified pixel format was invalid.");
         break;
      case DDERR_INVALIDPOSITION: 
         strcpy(errorText, "The position of the overlay on the destination is "\
            "no longer legal.");
         break;
      case DDERR_INVALIDRECT: 
         strcpy(errorText, "The provided rectangle was invalid.");
         break;
      case DDERR_INVALIDSTREAM: 
         strcpy(errorText, "The specified stream contains invalid data.");
         break;
      case DDERR_INVALIDSURFACETYPE:
         strcpy(errorText, "The surface was of the wrong type.");
         break;
      case DDERR_LOCKEDSURFACES:
         strcpy(errorText, "This operation failed due to a locked surface.");
         break;
      case DDERR_MOREDATA:
         strcpy(errorText, "There is more data available than the specified buffer "\
            "can hold.");
         break;
      case DDERR_NO3D:
         strcpy(errorText, "No 3-D hardware or emulation is present.");
         break;
      case DDERR_NOALPHAHW: 
         strcpy(errorText, "No alpha-acceleration hardware is present or available.");
         break;
      case DDERR_NOBLTHW: 
         strcpy(errorText, "No blitter hardware is present.");
         break;
      case DDERR_NOCLIPLIST: 
         strcpy(errorText, "No clip list is available.");
         break;
      case DDERR_NOCLIPPERATTACHED: 
         strcpy(errorText, "No DirectDrawClipper is attached to the surface.");
         break;
      case DDERR_NOCOLORCONVHW: 
         strcpy(errorText, "No color-conversion hardware is present or available.");
         break;
      case DDERR_NOCOLORKEY: 
         strcpy(errorText, "The surface does not currently have a color key.");
         break;
      case DDERR_NOCOLORKEYHW: 
         strcpy(errorText, "There is no hardware support for the destination color "\
            "key.");
         break;
      case DDERR_NOCOOPERATIVELEVELSET: 
         strcpy(errorText, "No cooperative level had been set.");
         break;
      case DDERR_NODC: 
         strcpy(errorText, "No device context exists for this surface.");
         break;
      case DDERR_NODDROPSHW: 
         strcpy(errorText, "No DirectDraw raster-operation (ROP) hardware is"\
            "available.");
         break;
      case DDERR_NODIRECTDRAWHW: 
         strcpy(errorText, "Hardware-only DirectDraw creation not possible.");
         break;
      case DDERR_NODIRECTDRAWSUPPORT: 
         strcpy(errorText, "DirectDraw support is not possible with the current"\
            "display driver.");
         break;
      case DDERR_NODRIVERSUPPORT: 
         strcpy(errorText, "Testing cannot proceed due to no display driver support.");
         break;
      case DDERR_NOEMULATION: 
         strcpy(errorText, "Software emulation not available.");
         break;
      case DDERR_NOEXCLUSIVEMODE: 
         strcpy(errorText, "This operation requires the application to have "\
            "exclusive mode.");
         break;
      case DDERR_NOFLIPHW: 
         strcpy(errorText, "Flipping visible surfaces not supported.");
         break;
      case DDERR_NOFOCUSWINDOW:
         strcpy(errorText, "Cannot create or set a device window without having "\
            "first set the focus window.");
         break;         
      case DDERR_NOGDI: 
         strcpy(errorText, "No GDI is present.");
         break;
      case DDERR_NOHWND:
         strcpy(errorText, "No cooperative-level window handle.");
         break;
      case DDERR_NOMIPMAPHW: 
         strcpy(errorText, "No mipmap-capable texture mapping hardware is present "\
            "or available.");
         break;
      case DDERR_NOMIRRORHW: 
         strcpy(errorText, "No mirroring hardware is present of available.");
         break;
      case DDERR_NOMONITORINFORMATION: 
         strcpy(errorText, "No monitor information exists.");
         break;
      case DDERR_NONONLOCALVIDMEM:
         strcpy(errorText, "No nonlocal video memory is available.");
         break;
      case DDERR_NOOPTIMIZEHW: 
         strcpy(errorText, "Optimized surfaces not supported.");
         break;
      case DDERR_NOOVERLAYDEST: 
         strcpy(errorText, "Overlay is not a destination.");
         break;
      case DDERR_NOOVERLAYHW: 
         strcpy(errorText, "No overlay hardware present or available.");
         break;
      case DDERR_NOPALETTEATTACHED: 
         strcpy(errorText, "No palette object is attached to the surface.");
         break;
      case DDERR_NOPALETTEHW: 
         strcpy(errorText, "No hardware support for 16- or 256-color palettes.");
         break;
      case DDERR_NORASTEROPHW: 
         strcpy(errorText, "No appropriate raster-operation hardware is present "\
            " or available.");
         break;
      case DDERR_NOROTATIONHW: 
         strcpy(errorText, "No rotation hardware is present or available.");
         break;
      case DDERR_NOSTEREOHARDWARE: 
         strcpy(errorText, "No stereo hardware is present or available.");
         break;
      case DDERR_NOSTRETCHHW: 
         strcpy(errorText, "No hardware support for stretching.");
         break;
      case DDERR_NOSURFACELEFT: 
         strcpy(errorText, "No hardware that supports stereo surfaces.");
         break;
      case DDERR_NOT4BITCOLOR:
         strcpy(errorText, "This operation requires a 4-bit color palette.");
         break;
      case DDERR_NOT4BITCOLORINDEX: 
         strcpy(errorText, "This operation requires a 4-bit color *index* palette.");
         break;
      case DDERR_NOT8BITCOLOR: 
         strcpy(errorText, "This operation requires an 8-bit color palette.");
         break;
      case DDERR_NOTAOVERLAYSURFACE: 
         strcpy(errorText, "Not an overlay surface.");
         break;
      case DDERR_NOTEXTUREHW: 
         strcpy(errorText, "No texture-mapping hardware is present or available.");
         break;
      case DDERR_NOTFLIPPABLE: 
         strcpy(errorText, "This surface cannot be flipped.");
         break;
      case DDERR_NOTFOUND: 
         strcpy(errorText, "The requested item was not found.");
         break;
      case DDERR_NOTINITIALIZED:
         strcpy(errorText, "DirectDraw object has not been initialized.");
         break;
      case DDERR_NOTLOADED: 
         strcpy(errorText, "Surface has not been allocated any memory.");
         break;
      case DDERR_NOTLOCKED: 
         strcpy(errorText, "Surface was not locked.");
         break;
      case DDERR_NOTPAGELOCKED: 
         strcpy(errorText, "Surface was not page-locked.");
         break;
      case DDERR_NOTPALETTIZED: 
         strcpy(errorText, "Surface is not palette-based.");
         break;
      case DDERR_NOVSYNCHW: 
         strcpy(errorText, "There is no hardware support for vertical blank or "\
            "synchronized operations.");
         break;
      case DDERR_NOZBUFFERHW: 
         strcpy(errorText, "There is no z-buffer hardware support.");
         break;
      case DDERR_NOZOVERLAYHW:
         strcpy(errorText, "Overlay surfaces cannot be z-layered: no hardware "\
            "support.");
         break;
      case DDERR_OUTOFCAPS: 
         strcpy(errorText, "The hardware needed for this operation has already "\
            "been allocated.");
         break;
      case DDERR_OUTOFMEMORY: 
         strcpy(errorText, "There is not enough memory to perform this operation.");
         break;
      case DDERR_OUTOFVIDEOMEMORY: 
         strcpy(errorText, "There is not enough *display* memory to perform this "\
            "operation.");
         break;
      case DDERR_OVERLAPPINGRECTS: 
         strcpy(errorText, "Source and destination rectangles are on the same "\
            "surface and overlap each other.");
         break;
      case DDERR_OVERLAYCANTCLIP: 
         strcpy(errorText, "The hardware does not support clipped overlays.");
         break;
      case DDERR_OVERLAYCOLORKEYONLYONEACTIVE: 
         strcpy(errorText, "Only one color key can be active on an overlay.");
         break;
      case DDERR_OVERLAYNOTVISIBLE :
         strcpy(errorText, "The specified overlay is hidden.");
         break;
      case DDERR_PALETTEBUSY: 
         strcpy(errorText, "The palette is busy.");
         break;
      case DDERR_PRIMARYSURFACEALREADYEXISTS: 
         strcpy(errorText, "A primary surface already exists.");
         break;
      case DDERR_REGIONTOOSMALL: 
         strcpy(errorText, "The specified clip region is too small.");
         break;
      case DDERR_SURFACEALREADYATTACHED: 
         strcpy(errorText, "The surface was already attached.");
         break;
      case DDERR_SURFACEALREADYDEPENDENT: 
         strcpy(errorText, "The surface was already dependent.");
         break;
      case DDERR_SURFACEBUSY: 
         strcpy(errorText, "The surface is busy.");
         break;
      case DDERR_SURFACEISOBSCURED: 
         strcpy(errorText, "Access to surface denied: surface is obscured.");
         break;
      case DDERR_SURFACELOST: 
         strcpy(errorText, "The surface has been lost: it must be restored.");
         break;
      case DDERR_SURFACENOTATTACHED: 
         strcpy(errorText, "The requested surface is not attached.");
         break;
      case DDERR_TOOBIGHEIGHT: 
         strcpy(errorText, "The requested height is too large.");
         break;
      case DDERR_TOOBIGSIZE:
         strcpy(errorText, "The requested size is too large.");
         break;
      case DDERR_TOOBIGWIDTH: 
         strcpy(errorText, "The requested width is too large.");
         break;
      case DDERR_UNSUPPORTED: 
         strcpy(errorText, "This operation is not supported.");
         break;
      case DDERR_UNSUPPORTEDFORMAT: 
         strcpy(errorText, "The pixel format is not supported by DirectDraw.");
         break;
      case DDERR_UNSUPPORTEDMASK: 
         strcpy(errorText, "The bitmask in the pixel format is not supported by "\
            "DirectDraw.");
         break;
      case DDERR_UNSUPPORTEDMODE: 
         strcpy(errorText, "The display is currently in an unsupported mode.");
         break;
      case DDERR_VERTICALBLANKINPROGRESS: 
         strcpy(errorText, "A vertical blank is in progress.");
         break;
      case DDERR_VIDEONOTACTIVE: 
         strcpy(errorText, "The video port is not active.");
         break;
      case DDERR_WASSTILLDRAWING: 
         strcpy(errorText, "The operation was still drawing.");
         break;
      case DDERR_WRONGMODE: 
         strcpy(errorText, "This surface cannot be restored: it was created in "\
            "a different mode.");
         break;
      case DDERR_XALIGN: 
         strcpy(errorText, "The rectangle was not horizontally aligned on a "\
            "required boundary.");
         break;
      default:
         strcpy(errorText, "Unknown Error");
         break;
   }

   throw(new DGException(errorText, errorCode, ET_DIRECTDRAW, fileName,
      lineNumber));
}

HRESULT CALLBACK EnumDisplayModes(LPDDSURFACEDESC2 lpDDSurfaceDesc,  
      LPVOID lpContext)
{
   DGGetGraphics()->displayModeList.Insert(new DGDisplayMode(lpDDSurfaceDesc->dwWidth,
      lpDDSurfaceDesc->dwHeight, lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount));

   return DDENUMRET_OK;
}
