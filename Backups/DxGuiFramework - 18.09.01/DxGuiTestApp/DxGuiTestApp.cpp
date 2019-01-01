/*DxGuiTestApp.cpp*/

#include <time.h>
#include <DxGuiFramework.h>
#include "DxGuiTestApp.h"
#include "RedWindow.h"
#include "BlueWindow.h"

//Instantiate the DxGuiTestApp class
DxGuiTestApp app;

//DxGuiTestApp method implementation
void DxGuiTestApp::InitApp()
{
   //Set the graphics mode
   dgGraphics->SetGraphicsMode(DGPoint(640, 480), WS_WINDOWED,
      CD_16BIT, BT_DOUBLE, true);

   //Initialize random number generator, in case I need it
   srand((unsigned)time( NULL ));

   //Set the font, in case I want to write some text
   dgGraphics->SetGDIFont(DGFont("Comic Sans MS", 20));

   //Create the main window
   BlueWindow* mainWindow = new BlueWindow();

   //Set the main window
   DGGetGui()->SetMainWindow(mainWindow);
}
