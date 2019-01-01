/*------------------------------------------------------------------------
File Name: DGGraphics.h
Description: This file contains the DGGraphics class, which manages
   the DirectDraw surfaces and controls and what is drawn to the screen.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#ifndef DGGRAPHICS_H
#define DGGRAPHICS_H

class DGGraphics
{
   friend HRESULT CALLBACK EnumDisplayModes(LPDDSURFACEDESC2 lpDDSurfaceDesc,  
      LPVOID lpContext);

public:
   DGGraphics();
   virtual ~DGGraphics();

   //Functions not needed, call SetGraphicsMode()
   //void Initialize(void); //arguments to be added later
   //void Destroy(void);

   void SetResolution(DGPoint res);
   void SetResolution(int hRes, int vRes);
   DGPoint GetResolution(void) {return screenRes;}

   void SetWindowedState(UINT winState);
   UINT GetWindowedState(void) {return windowedState;}

   void SetColorDepth(UINT clrDepth);
   UINT GetColorDepth(void); //return CD_16BIT, not the specialized modes
   //void SetAppColorDepth(UINT appClrDepth);
   //UINT GetAppColorDepth(void);

   void SetBufferingMode(UINT bufferMode);
   UINT GetBufferingMode(void) {return bufferingMode;}

   void SetSurfacePersistence(bool persistence);
   bool GetSurfacePersistence(void) {return SSPersistence;}

   void SetClientRect(RECT& rect) {clientRect = rect;}

   void SetGraphicsMode(DGPoint res, UINT winState, UINT clrDepth,
      UINT bufferMode, bool persistence = false);

   void BeginFrame(void);
   void EndFrame(void);

   //Bitmap functions
   DGBitmap* FC GetBitmap(UINT bitmapID);
   void LoadBitmap(UINT bitmapID, UINT priority);
   void LoadBitmap(UINT bitmapID, UINT priority, char* fileName);
   void LoadBitmapDimensions(UINT bitmapID, UINT priority,
      DGRectangle area);
   void LoadBitmapDimensions(UINT bitmapID, UINT priority,
      DGRectangle area, char* filename);
   void RemoveBitmap(UINT bitmapID);
   void RemoveAllBitmaps(void);
   void EnableAutoClean(bool clean, bool maxBmp, bool maxMem);
   void CleanMaxBitmaps(void);
   void CleanMaxBitmapMemory(void);
   void CleanBitmap(UINT bitmapID);
   void CleanBitmapByPriority(UINT bitmapID, UINT priority);
   void CleanAllBitmapsByPriority(UINT priority);
   void SetMaxBitmaps(UINT maxNumBmps);
   UINT GetMaxBitmaps(void) {return maxNumOfBitmaps;}
   void SetMaxBitmapMemory(UINT maxMem);
   UINT GetMaxBitmapMemory(void) {return maxAmountOfMemory;}
   UINT GetCurrentNumOfBitmaps(void) {return curNumOfBitmaps;}
   UINT GetCurrentBitmapMemory(void) {return curAmountOfMemory;}

   //Drawing Functions
   void FC LockSurface(void);
   void FC UnlockSurface(void);
   void FC FlipSurface(void);

   //Non-Blit Drawing Functions
   void FC SetPixel(int x, int y, DGColor& color);
   void FC DrawHorizontalLine(int x1, int x2, int y, DGColor& color);
   void FC DrawVerticalLine(int x, int y1, int y2, DGColor& color);
   void FC DrawLine(DGPoint& p1, DGPoint& p2, DGColor& color);
   void FC DrawRectangleBorder(DGRectangle& rect, DGColor& color);
   void FC DrawRect(DGRectangle& rect, DGColor& color);

   //Blit Drawing Functions
   void FC FillArea(DGRectangle& rect, DGColor& color);
   void FC DrawBitmap(DGPoint& location, UINT bitmapID);
   void FC DrawScaledBitmap(DGRectangle& rect, UINT bitmapID);
   void FC DrawTransparentBitmap(DGPoint& location, UINT bitmapID,
      DGColor& transparentColor);
   void FC DrawTransparentScaledBitmap(DGRectangle& rect, UINT bitmapID,
      DGColor& transparentColor);

   //GDI Drawing Functions
   void FlipToGDISurface(void);
   void FC SetGDIFont(DGFont& font);
   void FC DrawText(char* text, DGRectangle& rect, UINT flags);

   //Clipping Functions
   void FC AddClippingArea(DGRectangle& area);
   void FC RemoveClippingArea(DGRectangle& area);
   void FC ClearClippingAreas(void);

   static DGGraphics* instance;

   //DirectX-related functions
   void HandleDDrawError(UINT errorCode, HRESULT error, 
      char* fileName, UINT lineNumber);


private:
   //Pointer to DirectDraw object
   LPDIRECTDRAW7 lpDD;

   //Hardware capabilites structure
   DDCAPS ddCaps;

   //The surface description structure that can be used throughout
   //the DGGraphics member functions.
   DDSURFACEDESC2 ddsd;

   //The primary and secondary surface objects
   LPDIRECTDRAWSURFACE7 lpDDSPrimary;
   LPDIRECTDRAWSURFACE7 lpDDSSecondary;
   LPDIRECTDRAWSURFACE7 lpDDSDrawingSurface;

   //MS Windows info
   HWND hWnd;

   //Mode info
   DGPoint screenRes;

   UINT windowedState;
   UINT colorDepth;
   UINT bufferingMode;

   //Controls the persistence of the secondary surface.
   //When it is on, the secondary surface stays the same and is never
   //cleared by the framework. This makes flipping slower, as it flips by
   //blitting, but there is less redrawing involved, so it may save time
   //in the long run.
   bool SSPersistence;

   //When in windowed mode, we must know where the client area is so
   //that we can update the clipper and draw in the right place
   RECT clientRect;

   //The list of supported display modes
   //DGDisplayModeList displayModeList;
   DGDisplayModeList displayModeList;  

   //Bitmap list goes here

   bool autoClean;
   bool maxBitmaps;
   bool maxMemory;
   UINT maxNumOfBitmaps;
   UINT maxAmountOfMemory;
   UINT curNumOfBitmaps;
   UINT curAmountOfMemory;

   bool surfaceLocked;
   int bytesPerPixel;

   DGFont currentGDIFont;

   //Clipping area list goes here
   //Clipper for the primary surface: usually used by the framework
   //in windowed mode.
   LPDIRECTDRAWCLIPPER lpPSClipper;
   //Clipper for the secondary surface: usually used by the application
   LPDIRECTDRAWCLIPPER lpSSClipper;

   BYTE* videoBuffer;
   LONG bufferPitch;
};

//The callback function used to enumerate the supported display modes.
//Unfortunately it cannot be a member function of any class.
HRESULT CALLBACK EnumDisplayModes(LPDDSURFACEDESC2 lpDDSurfaceDesc,  
   LPVOID lpContext);

#endif