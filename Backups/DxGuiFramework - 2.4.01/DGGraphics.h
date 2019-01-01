/*------------------------------------------------------------------------
File Name: DGGraphics.h
Description: This file contains the DGGraphics class, which manages
   the DirectDraw surfaces and controls and what is drawn to the screen.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#ifndef DGGRAPHICS_H
#define DGGRAPHICS_H

class DGSurface;

class DGGraphics
{
   friend HRESULT CALLBACK EnumDisplayModes(LPDDSURFACEDESC2 lpDDSurfaceDesc,  
      LPVOID lpContext);
   friend class DGBitmap;

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

   void SetBufferingMode(UINT bufferMode);
   UINT GetBufferingMode(void) {return bufferingMode;}

   void SetSurfacePersistence(bool persistence);
   bool GetSurfacePersistence(void) {return SSPersistence;}

   void SetClientRect(RECT& rect) {clientRect = rect;}

   void SetGraphicsMode(DGPoint res, UINT winState, UINT clrDepth,
      UINT bufferMode = BT_SINGLE, bool persistence = false);

   void BeginFrame(void);
   void EndFrame(void);

   //Bitmap functions
   DGBitmap* FC GetBitmap(UINT bitmapID);
   void LoadBitmap(UINT bitmapID, UINT priority);
   void LoadBitmap(UINT bitmapID, UINT priority, char* fileName);
   void LoadBitmapDimensions(UINT bitmapID, UINT priority,
      DGArea& area);
   void LoadBitmapDimensions(UINT bitmapID, UINT priority,
      DGArea& area, char* fileName);
   void RemoveBitmap(UINT bitmapID);
   void RemoveAllBitmaps(void);
   void DeleteBitmap(UINT bitmapID);
   void DeleteAllBitmaps(void);
   void EnableAutoClean(bool clean, bool maxBmp, bool maxMem);
   void CleanMaxBitmaps(void);
   void CleanMaxBitmapMemory(void);
   void CleanBitmap(UINT bitmapID);
   void CleanBitmapByPriority(UINT priority);
   void CleanAllBitmapsByPriority(UINT priority);
   void SetMaxBitmaps(UINT maxNumBmps);
   UINT GetMaxBitmaps(void) {return maxNumOfBitmaps;}
   void SetMaxBitmapMemory(UINT maxMem);
   UINT GetMaxBitmapMemory(void) {return maxAmountOfMemory;}
   UINT GetCurrentNumOfBitmaps(void) {return curNumOfBitmaps;}
   UINT GetCurrentBitmapMemory(void) {return curAmountOfMemory;}
   void SetTransparentColor(UINT bitmapID, DGColor& transparentColor);

   //Drawing Functions
   void FC LockSurface(void);
   void FC UnlockSurface(void);
   void FC FlipSurface(void);

   //Non-Blit Drawing Functions
   void FC SetPixel(int x, int y, DGColor& color);
   void FC DrawHorizontalLine(int x1, int x2, int y, DGColor& color);
   void FC DrawVerticalLine(int x, int y1, int y2, DGColor& color);
   void FC DrawLine(DGPoint& p1, DGPoint& p2, DGColor& color);
   void FC DrawRectangle(DGRectangle& rect, DGColor& color);
   void FC DrawFilledRectangle(DGRectangle& rect, DGColor& color);

   //Blit Drawing Functions
   void FC FillArea(DGRectangle& rect, DGColor& color);
   void FC FillScreen(DGColor& color);
   void FC DrawBitmap(DGPoint& location, UINT bitmapID);
   void FC DrawScaledBitmap(DGArea& area, UINT bitmapID);
   void FC DrawTransparentBitmap(DGPoint& location, UINT bitmapID,
      DGColor& transparentColor);
   void FC DrawTransparentScaledBitmap(DGArea& area, UINT bitmapID,
      DGColor& transparentColor);
   void FC DrawTransparentBitmap(DGPoint& location, UINT bitmapID);
   void FC DrawTransparentScaledBitmap(DGArea& area, UINT bitmapID);   

   //GDI Drawing Functions
   void FlipToGDISurface(void);
   void FC SetGDIFont(DGFont& font);
   void FC SetTextTransparency(int mode);
   void FC SetTextColor(DGColor& color);
   void FC SetTextBackgroundColor(DGColor& color);
   void FC DrawText(char* text, DGRectangle& rect, UINT flags);

   //Clipping Functions
   void FC AddClippingArea(DGRectangle& area);
   void FC RemoveClippingArea(void);
   void FC ClearClippingAreas(void);

   static DGGraphics* instance;

   //Functions to get and release a DGSurface
   DGSurface* FC GetSurface(DGArea& area);
   void FC ReleaseSurface(DGSurface* surface = NULL);
   DGSurface* GetCurrentSurface(void) {return currentSurface;}

   //DirectX-related functions
   void HandleDDrawError(UINT errorCode, HRESULT error, 
      char* fileName, UINT lineNumber);

private:
   void FC RestoreAllSurfaces(void);
   void FC DestroyAllSurfaces(void);
   void FC ClearPrimarySurface(void);

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
   DGDisplayModeList displayModeList;  

   //The list which stores and manages the bitmaps
   DGBitmapList bitmapList;

   bool autoClean;
   bool maxBitmaps;
   bool maxMemory;
   UINT maxNumOfBitmaps;
   UINT maxAmountOfMemory;
   UINT curNumOfBitmaps;
   UINT curAmountOfMemory;

   bool surfaceLocked;
   int bytesPerPixel;

   //Text information
   DGFont currentGDIFont;
   int textTransparencyMode;
   DGColor textColor;
   DGColor textBackgroundColor;
   
   //Clipper for the primary surface: usually used by the framework
   //in windowed mode.
   LPDIRECTDRAWCLIPPER lpPSClipper;
   //Clipper for the drawing surface: usually used by the application
   LPDIRECTDRAWCLIPPER lpDSClipper;

   //Whether there is clipping on the drawing surface
   bool clipping;
   //The current clipping area
   RGNDATA* clippingArea;
   DGRectangle clippingRect;

   //The current DGSurface
   DGSurface* currentSurface;

   UCHAR* videoBuffer;
   LONG bufferPitch;
};

//The callback function used to enumerate the supported display modes.
//Unfortunately it cannot be a member function of any class.
HRESULT CALLBACK EnumDisplayModes(LPDDSURFACEDESC2 lpDDSurfaceDesc,  
   LPVOID lpContext);

#endif