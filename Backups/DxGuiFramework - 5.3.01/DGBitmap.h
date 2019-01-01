/*------------------------------------------------------------------------
File Name: DGBitmap.h
Description: This file contains the DGGBitmap class, which represents
	a bitmap stored in memory. An object of this class is able to load
	as well as store bitmaps.
Version:
   1.0.0    25.02.2000  Created the file
------------------------------------------------------------------------*/

#ifndef DGBITMAP_H
#define DGBITMAP_H

class DGBitmap
{
public:
   DGBitmap();
   DGBitmap(UINT bitmapID, UINT bitmapPriority = 1);
   DGBitmap(UINT bitmapID, UINT bitmapPriority, UINT resourceID);
   DGBitmap(UINT bitmapID, UINT bitmapPriority, UINT resourceID,
      DGRectangle& dimensions);
   DGBitmap(UINT bitmapID, UINT bitmapPriority, char* bitmapFileName);
   DGBitmap(UINT bitmapID, UINT bitmapPriority, char* bitmapFileName,
      DGRectangle& dimensions);
   virtual ~DGBitmap();

   void SetID(UINT bitmapID) {id = bitmapID;}
   UINT GetID(void) {return id;}
   void SetPriority(UINT bitmapPriority) {priority = bitmapPriority;}
   UINT GetPriority(void) {return priority;}
   bool IsResourceBitmap(void) {return resourceBitmap;}
   char* const GetFileName(void) {return fileName;}
   DGPoint GetDimensions(void) {return DGPoint(width, height);}
   bool IsLoaded(void) {return isLoaded;}
   int GetWidth(void) {return width;}
   int GetHeight(void) {return height;}

   LPDIRECTDRAWSURFACE7 GetDDSurface(void);
   void FC SetTransparentColor(DGColor& color);

   void FC LoadBitmap(UINT resourceID);
   void FC LoadBitmap(UINT resourceID, DGRectangle& bitmapDimensions);
   void FC LoadBitmap(char* bitmapFileName);
   void FC LoadBitmap(char* bitmapFileName, 
      DGRectangle& bitmapDimensions);
   void FC DestroyBitmap(void);
   void FC ReloadBitmap(void);
   void FC RestoreBitmap(void);

private:
   void LoadBitmapFromFile(DGRectangle& rect, char* bitmapFileName);
   DGPoint FindBitmapSize(char* bitmapFileName);

   UINT id;
   UINT priority;

   bool isLoaded;
   bool useDimensions;
   bool resourceBitmap;
   char fileName[128];

   //The area in the file that this was loaded from
   DGRectangle dimensions;

   int width;
   int height;
   UINT colorDepth;

   //The color to draw transparently: only is transparent when
   //a transparent blit function is called.
   DGColor transparentColor;

   //DirectDraw surface: stores the loaded bitmap
   LPDIRECTDRAWSURFACE7 lpDDSBitmap;

   UINT memoryUsage;
};

#endif