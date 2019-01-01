/*------------------------------------------------------------------------
File Name: DGBitmap.cpp
Description: This file contains the DGBitmap class implementation.
   A DGBitmap object is used to store a bitmap and its information for
   use in the framework.
Version:
   1.0.0    24.02.2001  Created the file
------------------------------------------------------------------------*/

#include <fstream.h>
#include "DxGuiFramework.h"

DGBitmap::DGBitmap()
{
   id = IDB_NO_ID;
   priority = 1;

   isLoaded = false;
   useDimensions = false;
   resourceBitmap = false;
   fileName[0] = '\0';

   int width = 0;
   int height = 0;

   //Default transparent color is magenta
   transparentColor.SetColor(255, 0, 255);

   lpDDSBitmap = NULL;

   memoryUsage = 0;
}

DGBitmap::DGBitmap(UINT bitmapID, UINT bitmapPriority)
{
   id = bitmapID;
   priority = bitmapPriority;

   isLoaded = false;
   useDimensions = false;
   resourceBitmap = false;
   fileName[0] = '\0';

   int width = 0;
   int height = 0;

   //Default transparent color is magenta
   transparentColor.SetColor(255, 0, 255);

   lpDDSBitmap = NULL;

   memoryUsage = 0;
}

DGBitmap::DGBitmap(UINT bitmapID, UINT bitmapPriority, UINT resourceID)
{
   //This function will be completed after resource files have been
   //implemented.
}

DGBitmap::DGBitmap(UINT bitmapID, UINT bitmapPriority, UINT resourceID,
      DGArea& dimensions)
{
   //This function will be completed after resource files have been
   //implemented.
}

DGBitmap::DGBitmap(UINT bitmapID, UINT bitmapPriority, char* bitmapFileName)
{
   id = bitmapID;
   priority = bitmapPriority;

   //Default transparent color is magenta
   transparentColor.SetColor(255, 0, 255);

   LoadBitmap(bitmapFileName);
}

DGBitmap::DGBitmap(UINT bitmapID, UINT bitmapPriority, char* bitmapFileName,
      DGArea& bitmapDimensions)
{
   id = bitmapID;
   priority = bitmapPriority;

   //Default transparent color is magenta
   transparentColor.SetColor(255, 0, 255);

   LoadBitmap(bitmapFileName, bitmapDimensions);
}
 
DGBitmap::~DGBitmap()
{
   if(lpDDSBitmap != NULL)
      lpDDSBitmap->Release();
}

LPDIRECTDRAWSURFACE7 DGBitmap::GetDDSurface(void)
{
   if(lpDDSBitmap == NULL)
      ReloadBitmap();

   return lpDDSBitmap;
}

void FC DGBitmap::SetTransparentColor(DGColor& color)
{
   transparentColor = color;
   if(lpDDSBitmap != NULL)
   {
      UINT colorDepth = dgGraphics->colorDepth;
      DDCOLORKEY colorKey;
      switch(colorDepth)
      {
         case CD_16BIT5:
            colorKey.dwColorSpaceHighValue = transparentColor.To16Bit5();
            colorKey.dwColorSpaceLowValue = colorKey.dwColorSpaceHighValue;
            break;
         case CD_16BIT6:
            colorKey.dwColorSpaceHighValue = transparentColor.To16Bit6();
            colorKey.dwColorSpaceLowValue = colorKey.dwColorSpaceHighValue;
            break;
         default:
            colorKey.dwColorSpaceHighValue = transparentColor.To32Bit();
            colorKey.dwColorSpaceLowValue = colorKey.dwColorSpaceHighValue;
            break;
      }

      HRESULT result = lpDDSBitmap->SetColorKey(DDCKEY_SRCBLT, &colorKey);

      switch(result)
      {
         case DD_OK:
            break;
         case DDERR_WRONGMODE:
         case DDERR_SURFACELOST:
            RestoreBitmap();
            break;
         default:
            dgGraphics->HandleDDrawError(EC_DDCOLORKEY, result, 
               __FILE__, __LINE__);
      }  
   }
}

void FC DGBitmap::LoadBitmap(UINT resourceID)
{
   //This function will be completed after resource files have been
   //implemented.
}

void FC DGBitmap::LoadBitmap(UINT resourceID, DGArea& bitmapDimensions)
{
   //This function will be completed after resource files have been
   //implemented.
}

void FC DGBitmap::LoadBitmap(char* bitmapFileName)
{
   HRESULT result;

   DGPoint bitmapSize = FindBitmapSize(bitmapFileName);

   //Create the DirectDraw surface for the bitmap
   DDSURFACEDESC2 ddsd;
   memset(&ddsd, 0, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd);    
   ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; 
   ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN; 
   ddsd.dwWidth = bitmapSize.x; 
   ddsd.dwHeight = bitmapSize.y; 
   
   result = dgGraphics->lpDD->CreateSurface(&ddsd, &lpDDSBitmap, NULL); 

   if(result != DD_OK)
      dgGraphics->HandleDDrawError(EC_DDSETGRAPHMODE, result, 
         __FILE__, __LINE__);

   LoadBitmapFromFile(DGArea(0, 0, bitmapSize.x, bitmapSize.y),
      bitmapFileName);

   isLoaded = true;
   useDimensions = false;
   resourceBitmap = false;
   strcpy(fileName, bitmapFileName);

   width = bitmapSize.x;
   height = bitmapSize.y;

   memset(&ddsd, 0, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd); 
   lpDDSBitmap->GetSurfaceDesc(&ddsd);

   memoryUsage = ddsd.lPitch * ddsd.dwHeight;

   SetTransparentColor(transparentColor);
}

void FC DGBitmap::LoadBitmap(char* bitmapFileName, DGArea& bitmapDimensions)
{
   HRESULT result;

   DGPoint bitmapSize = FindBitmapSize(bitmapFileName);

   assert(bitmapDimensions.left >= 0 && bitmapDimensions.left < bitmapSize.x &&
      bitmapDimensions.top >= 0 && bitmapDimensions.top < bitmapSize.y &&
      bitmapDimensions.width >= 0 && bitmapDimensions.height >= 0 &&
      bitmapDimensions.Right() >= 0 && 
      bitmapDimensions.Right() <= bitmapSize.x &&
      bitmapDimensions.Bottom() >= 0 && 
      bitmapDimensions.Bottom() <= bitmapSize.y);

   //Create the DirectDraw surface for the bitmap
   DDSURFACEDESC2 ddsd;
   memset(&ddsd, 0, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd);    
   ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; 
   ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN; 
   ddsd.dwWidth = bitmapDimensions.width; 
   ddsd.dwHeight = bitmapDimensions.height; 
   
   result = dgGraphics->lpDD->CreateSurface(&ddsd, &lpDDSBitmap, NULL); 

   if(result != DD_OK)
      dgGraphics->HandleDDrawError(EC_DDSETGRAPHMODE, result, 
         __FILE__, __LINE__);

   LoadBitmapFromFile(bitmapDimensions, bitmapFileName);

   isLoaded = true;
   useDimensions = true;
   resourceBitmap = false;
   strcpy(fileName, bitmapFileName);

   dimensions = bitmapDimensions;

   width = bitmapDimensions.width;
   height = bitmapDimensions.height;

   memset(&ddsd, 0, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd); 
   lpDDSBitmap->GetSurfaceDesc(&ddsd);

   memoryUsage = ddsd.lPitch * ddsd.dwHeight;

   SetTransparentColor(transparentColor);
}

void FC DGBitmap::DestroyBitmap()
{
   if(lpDDSBitmap != NULL)
   {
      lpDDSBitmap->Release();
      lpDDSBitmap = NULL;
   }

   isLoaded = false;
   memoryUsage = 0;
}

void FC DGBitmap::ReloadBitmap()
{
   //If the surface is NULL, is means it was lost and
   //needs to be reloaded.
   if(isLoaded && lpDDSBitmap != NULL)
      return;

   if(resourceBitmap)
   {
      if(useDimensions)
         LoadBitmap(id, dimensions);
      else
         LoadBitmap(id);
   }

   else
   {
      if(useDimensions)
         LoadBitmap(fileName, dimensions);
      else
         LoadBitmap(fileName);
   }

   SetTransparentColor(transparentColor);
}

//This function is to be called when surfaces are lost
void FC DGBitmap::RestoreBitmap()
{
   HRESULT result;
   
   result = lpDDSBitmap->Restore();

   switch(result)
   {
      case DD_OK:
         break;
      case DDERR_WRONGMODE:
         lpDDSBitmap = NULL;
         break;
      default:
         dgGraphics->HandleDDrawError(EC_DDRESTORESURFACES, result, 
            __FILE__, __LINE__);
   }

   ReloadBitmap();
}

void DGBitmap::LoadBitmapFromFile(DGArea& rect, char* bitmapFileName)
{
   char message[256];

   //Reads the bitmap file into the buffer
   fstream bitmapFile(bitmapFileName, ios::in | ios::binary | ios::nocreate);

   //If file cannot be opened, Error
   if(bitmapFile.fail())
   {
      sprintf(message, "The file %s could not be opened.", bitmapFileName);
      throw new DGException(message, EC_BMBITMAPLOAD, ET_BITMAP,
         __FILE__, __LINE__);
   }

   //If file is not a bitmap, Error
   BITMAPFILEHEADER bmfh;
   bitmapFile.read((UCHAR*)&bmfh, sizeof(bmfh));
   if(bmfh.bfType != 0x4D42)
   {
      sprintf(message, "The file %s is not a bitmap file.", bitmapFileName);
      throw new DGException(message, EC_BMBITMAPLOAD, ET_BITMAP,
         __FILE__, __LINE__);
   }

   BITMAPINFOHEADER bmih;
   bitmapFile.read((UCHAR*)&bmih, sizeof(bmih));

   //We are only interested in 24-bit bitmaps
   if(bmih.biBitCount != 24)
   {
      sprintf(message, "The file %s is not a 24-bit bitmap.", bitmapFileName);
      throw new DGException(message, EC_BMBITMAPLOAD, ET_BITMAP,
         __FILE__, __LINE__);
   }

   //We don't want compressed bitmaps
   if(bmih.biCompression != BI_RGB)
   {
      sprintf(message, "%s: compressed bitmaps cannot be loaded.", 
         bitmapFileName);
      throw new DGException(message, EC_BMBITMAPLOAD, ET_BITMAP,
         __FILE__, __LINE__);
   }

   int bytesPerLine = bmih.biWidth * 3;
   RGBTRIPLE pixel;
   UCHAR* videoBuffer;
   int bufferPitch;
   int bufferPosition = 0;
   DGColor color;

   //Lock the surface for drawing
   HRESULT result;
   DDSURFACEDESC2 ddsd;
   memset(&ddsd, 0, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd);

   result = lpDDSBitmap->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR |
      DDLOCK_WAIT, NULL);

   switch(result)
   {
      case DDERR_SURFACELOST:
         lpDDSBitmap->Restore();
         result = lpDDSBitmap->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR |
            DDLOCK_WAIT, NULL);
         if(result != DD_OK)
            dgGraphics->HandleDDrawError(EC_DDLOCKSURFACE, result, 
               __FILE__, __LINE__);
         break;
      case DD_OK:
         videoBuffer = (UCHAR*)ddsd.lpSurface;
         bufferPitch = ddsd.lPitch;
         break;
      default:
         lpDDSBitmap->Unlock(NULL);
         dgGraphics->HandleDDrawError(EC_DDLOCKSURFACE, result, 
            __FILE__, __LINE__);
         break;
   }
   
#ifdef _DEBUG
   lpDDSBitmap->Unlock(NULL);
#endif

   //Bitmaps have padding so that the end of each scanline is on the
   //32-bit boundary.  Necessary padding for this bitmap is calculated
   int padding = bmih.biWidth % 4;

   //Find initial buffer position
   switch(dgGraphics->colorDepth)
   {
      case CD_16BIT5:
      case CD_16BIT6:
         bufferPosition = (rect.height - 1) * (bufferPitch >> 1);
         break;
      case CD_24BIT:
         bufferPosition = (rect.height - 1) * bufferPitch;
         break;
      case CD_32BIT:
         bufferPosition = (rect.height - 1) * (bufferPitch >> 2);
         break;
   }

   //Find initial position in file
   bitmapFile.ignore((bytesPerLine + padding) * 
      (bmih.biHeight - (rect.top + rect.height)));
   
   for(int y = rect.height - 1; y >= 0; y--)
   {
      //Ignore the first pixels in the row if necessary
      bitmapFile.ignore(rect.left * 3);
      for(int x = 0; x < rect.width; x++)
      {
         //Read the pixel from the file
         bitmapFile.read((char *)&pixel, sizeof(pixel));
         color.r = pixel.rgbtRed;
         color.g = pixel.rgbtGreen;
         color.b = pixel.rgbtBlue;
         //Write the pixel on the bitmap surface
         switch(dgGraphics->colorDepth)
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

      //Move the file pointer to the beginning of the next bitmap line
      bitmapFile.ignore(bytesPerLine - ((rect.left + rect.width) * 3) + 
         padding);

      //Move the bufferPosition variable to the next line
      switch(dgGraphics->colorDepth)
      {
         case CD_16BIT5:
         case CD_16BIT6:
            bufferPosition = bufferPosition - ((bufferPitch >> 1) + rect.width);
            break;
         case CD_24BIT:
            bufferPosition = bufferPosition - (bufferPitch + (rect.width * 3));
            break;
         case CD_32BIT:
            bufferPosition = bufferPosition - ((bufferPitch >> 2) + rect.width);
            break;
      }
   }

#ifndef _DEBUG
   lpDDSBitmap->Unlock(NULL);
#endif

   bitmapFile.close();
}

DGPoint DGBitmap::FindBitmapSize(char* bitmapFileName)
{
   char message[256];

   //Reads the bitmap file into the buffer
   fstream bitmapFile(bitmapFileName, ios::in | ios::binary | ios::nocreate);

   //If file cannot be opened, Error
   if(bitmapFile.fail())
   {
      sprintf(message, "The file %s could not be opened.", bitmapFileName);
      throw new DGException(message, EC_BMBITMAPSIZE, ET_BITMAP,
         __FILE__, __LINE__);
   }

   //If file is not a bitmap, Error
   BITMAPFILEHEADER bmfh;
   bitmapFile.read((UCHAR*)&bmfh, sizeof(bmfh));
   if(bmfh.bfType != 0x4D42)
   {
      sprintf(message, "The file %s is not a bitmap file.", bitmapFileName);
      throw new DGException(message, EC_BMBITMAPSIZE, ET_BITMAP,
         __FILE__, __LINE__);
   }

   BITMAPINFOHEADER bmih;
   bitmapFile.read((UCHAR*)&bmih, sizeof(bmih));
   bitmapFile.close();

   return DGPoint(bmih.biWidth, bmih.biHeight);
}