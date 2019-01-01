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

/*   dgGraphics->LockSurface();
   dgGraphics->DrawFilledRectangle(DGRectangle(20, 20, 80, 50), 
      DGColor(156, 45, 101));
   dgGraphics->UnlockSurface();   

   srand((unsigned)time( NULL ));
*/
   dgGraphics->TestBitmap("Bitmaps/Stones Large.bmp");
}

void DGSampleApplication::PreGUIDraw()
{
/*   dgGraphics->LockSurface();

   dgGraphics->DrawFilledRectangle(DGRectangle(rand() % 640, 
      rand() % 480, rand() % 640, rand() % 480), 
      DGColor(rand() % 255, rand() % 255, rand() % 255));
 
   dgGraphics->UnlockSurface();*/
}
