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
   dgGraphics->SetGraphicsMode(DGPoint(640, 480), WS_FULLSCREEN,
      CD_16BIT, BT_DOUBLE, true);

//   dgGraphics->FillArea(DGRectangle(20, 20, 120, 120), 
//      DGColor(232, 120, 183));
/*   dgGraphics->LockSurface();
   dgGraphics->DrawFilledRectangle(DGRectangle(20, 20, 80, 50), 
      DGColor(156, 45, 101));
   dgGraphics->UnlockSurface();   
*/
   srand((unsigned)time( NULL ));

   dgGraphics->LoadBitmap(1, 1, "Bitmaps/Stones Large.bmp");
   //dgGraphics->TestBitmap("Bitmaps/Stones Large.bmp");
}

void DGSampleApplication::PreGUIDraw()
{
   dgGraphics->DrawBitmap(DGPoint(10, 10), 1);
/*   DGRectangle rect;
   rect.left = rand() % 640;
   rect.right = rand() % 640;
   while(rect.right == rect.left)
      rect.right = rand() % 640;

   rect.top = rand() % 480;
   rect.bottom = rand() % 480;
   while(rect.bottom == rect.top)
      rect.bottom = rand() % 480;

   dgGraphics->FillArea(rect, 
      DGColor(rand() % 255, rand() % 255, rand() % 255));*/
}
