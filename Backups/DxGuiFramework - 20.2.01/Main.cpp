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

   dgGraphics->BeginFrame();
   dgGraphics->FillScreen(DGColor(0, 0, 0));
   dgGraphics->LockSurface();
   
   dgGraphics->SetPixel(4, 4, DGColor(255, 0, 0));
   dgGraphics->SetPixel(3, 3, DGColor(0, 0, 255));
   dgGraphics->SetPixel(27, 27, DGColor(255, 0, 0));

   dgGraphics->UnlockSurface();
   dgGraphics->EndFrame();

   srand((unsigned)time( NULL ));

}

void DGSampleApplication::PreGUIDraw()
{
   dgGraphics->LockSurface();
   dgGraphics->SetPixel(rand() % 640, rand() % 480,
      DGColor(rand() % 255, rand() % 255, rand() % 255));
   dgGraphics->UnlockSurface();
}
