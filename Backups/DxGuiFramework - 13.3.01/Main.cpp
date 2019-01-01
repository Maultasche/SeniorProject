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

   dgGraphics->SetGDIFont(DGFont("Comic Sans MS", 50));
   //dgGraphics->LoadBitmap(1, 1, "Bitmaps/Stars.bmp");
   //dgGraphics->AddClippingArea(DGRectangle(40, 40, 300, 300));
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
   dgGraphics->DrawText("This is a test string", DGRectangle(0, 0, 400, 50),
      DT_LEFT);
}
