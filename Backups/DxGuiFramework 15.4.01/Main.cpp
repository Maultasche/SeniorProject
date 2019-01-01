/*Main.cpp*/

#include <time.h>
#include "DxGuiFramework.h"

class DGSampleApplication : public DGApplication
{
public:
   void InitApp();
   void PreGUIDraw();
};

//User defines DxGuiApplication object
DGSampleApplication app;

//User lists overridden DxGuiApplication functions
void DGSampleApplication::InitApp()
{
   dgGraphics->SetGraphicsMode(DGPoint(640, 480), WS_WINDOWED,
      CD_16BIT, BT_DOUBLE, true);

   srand((unsigned)time( NULL ));

   DGWindow window(100, false);

   dgGraphics->SetGDIFont(DGFont("Comic Sans MS", 20));
   dgGraphics->LoadBitmap(1, 1, "Bitmaps/Stones Large.bmp");
   //dgGraphics->AddClippingArea(DGRectangle(20, 20, 300, 300));
}

void DGSampleApplication::PreGUIDraw()
{

/*   dgGraphics->SetTransparentColor(1, DGColor(128, 128, 128));  
   dgGraphics->DrawBitmap(DGPoint(0, 0), 1);
   //dgGraphics->SetTransparentColor(1, DGColor(128, 128, 128));
   dgGraphics->DrawTransparentBitmap(DGPoint(220, 0),
      1);
   //dgGraphics->SetTransparentColor(1, DGColor(128, 128, 128));
   dgGraphics->DrawTransparentBitmap(DGPoint(0, 220),
      1);
   dgGraphics->DrawTransparentBitmap(DGPoint(220, 220),
      1);*/
   DGSurface* surface = dgGraphics->
      GetSurface(DGArea(100, 100, 200, 20));
   surface->LockSurface();
   surface->DrawHorizontalLine(0, 400, 19, DGColor(255, 0, 0));
   surface->DrawVerticalLine(20, -10, 400, DGColor(255, 0, 255));
   surface->DrawLine(DGPoint(-30, 50), DGPoint(212, 15), DGColor(0, 255, 0));
   surface->UnlockSurface();
   //surface->DrawBitmap(DGPoint(0, 0), 1);
   //surface->DrawText("This is hopefully a really long a test string", DGRectangle(0, 0, 400, 50),
   //   DT_LEFT);
   
   dgGraphics->ReleaseSurface();
}
