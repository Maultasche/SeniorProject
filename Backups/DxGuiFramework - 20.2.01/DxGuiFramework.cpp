/*DxGuiFramework.cpp*/

#include "DxGuiFramework.h"

//Global Object Pointer Definitions
DGGraphics* dgGraphics = NULL;
DGInput* dgInput = NULL;

//Static variable needs to be initialized to prevent linker errors
DGApplication* DGApplication::instance = NULL;
DGGraphics* DGGraphics::instance = NULL;

//Global Function Definitions
DGApplication* DGGetApp(void) {return DGApplication::instance;}
DGGraphics* DGGetGraphics(void) {return DGGraphics::instance;}
DGGui* DGGetGui(void) {return DGGetApp()->GetGui();}

//Declare Windows Message Function
LRESULT CALLBACK WindowsMessageFunction(HWND hWnd, 
   UINT uMsg, WPARAM wParam, LPARAM lParam);

//General Exception-Handling Function
void HandleException(DGException* exception);

//The WinMain function is required for any Windows program.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine, int nCmdShow)
{
   OutputDebugString("WinMain\n");

   assert(DGGetApp() != NULL);

   try
   {
      DGApplication* application = DGGetApp();

      //Call PreInitApp() to get MS Window settings
      application->PreInitApp();
   
      //Get the Windows class from the application object
      WNDCLASSEX winClass = application->windowClass;

      //The message function must be this one.
      winClass.lpfnWndProc = WindowsMessageFunction;
      winClass.hInstance = hInstance;

      //Register the Windows class
      if(!RegisterClassEx(&winClass))
         return 0;

      DGWindowSettings winSettings = application->windowSettings;

      if(!(application->hWnd = CreateWindow(winClass.lpszClassName,
         winSettings.windowName, winSettings.dwStyle,
         winSettings.xPos, winSettings.yPos, 
         winSettings.nWidth, winSettings.nHeight, 
         NULL, winSettings.hMenu, hInstance, NULL)))
         return 0;

      //Allocate the global DGGraphics and DGInput objects
      //This must be done *after* the window is created
      dgGraphics = new DGGraphics();
      dgInput = new DGInput();

      //dgGraphics->SetGraphicsMode(DGPoint(640, 480), WS_WINDOWED,
      //   CD_16BIT, BT_DOUBLE);

      application->InitApp();

      application->RunApp();
   }

   catch(DGException* exception)
   {
      HandleException(exception);
      delete exception;
   }

   if(dgGraphics != NULL)
      delete dgGraphics;
   if(dgInput != NULL)
      delete dgInput;

   return 0;
}

LRESULT CALLBACK WindowsMessageFunction(HWND hWnd, 
   UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   return DGGetApp()->WindowsMessageFunction(hWnd, 
      uMsg, wParam, lParam);
}

void HandleException(DGException* exception)
{
   char outputText[1024];

   sprintf(outputText, "%s\nFile: %s, Line: %i", exception->errorMessage,
      exception->fileName, exception->lineNumber);

   switch(exception->errorType)
   {
      //It's a DirectDraw error
      case ET_DIRECTDRAW:
      {
         switch(exception->errorCode)
         {
            case EC_DDINIT:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Initialization Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;

            case EC_DDSETGRAPHMODE:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw SetGraphicsMode Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;
            
            case EC_DDLOCKSURFACE:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Surface Locking Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;

            case EC_DDUNLOCKSURFACE:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Surface Unlocking Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;
            case EC_DDFLIPSURFACE:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Surface Flipping Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;
            case EC_DDRESTORESURFACES:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Surface Restore Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;
            case EC_DDFILLSCREEN:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Screen Fill Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;
            case EC_DDCLEARPRIMARY:
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Primary Surface Clearing Error Has "\
                  "Occurred", MB_OK | MB_ICONERROR);
               break;
            default: 
            {
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "An Unknown DirectDraw Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;
            }
         }
         break;
      }

      //The type of error is unknown
      default:
      {
         MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
            "An Unknown Error Has Occurred", MB_OK | MB_ICONERROR);
      }
   }
}