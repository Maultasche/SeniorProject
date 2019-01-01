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

   dgGraphics->LoadBitmap(1, 1, "Bitmaps/Stars.bmp");
}

void DGSampleApplication::PreGUIDraw()
{
  dgGraphics->DrawTransparentBitmap(DGPoint(0, 0), 1, 
      DGColor(128, 128, 128));
  dgGraphics->DrawTransparentBitmap(DGPoint(220, 0), 1, 
      DGColor(255, 0, 0));
  dgGraphics->DrawTransparentBitmap(DGPoint(0, 220), 1, 
      DGColor(0, 255, 0));
  dgGraphics->DrawTransparentBitmap(DGPoint(220, 220), 1, 
      DGColor(0, 0, 255));
}
