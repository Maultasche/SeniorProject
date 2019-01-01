/*Main.cpp*/

#include "DxGuiFramework.h"

class DGSampleApplication : public DGApplication
{
public:
   void InitApp();
};

//User defines DxGuiApplication object
DGSampleApplication app;

//User lists overridden DxGuiApplication functions
void DGSampleApplication::InitApp()
{
   dgGraphics->SetGraphicsMode(DGPoint(640, 480), WS_WINDOWED,
      CD_16BIT, BT_DOUBLE);
}