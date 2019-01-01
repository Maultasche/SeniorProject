/*DxGuiFramework.cpp*/

#include "DxGuiFramework.h"

//Global Object Pointer Definitions
DGGraphics* dgGraphics;
DGInput* dgInput;

//Static variable needs to be initialized to prevent linker errors
DGApplication* DGApplication::instance = NULL;

//Global Function Definitions
DGApplication* DGGetApp(void) {return DGApplication::instance;}
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

   try
   {
      DGApplication* application = DGGetApp();

      //Call PreInitApp() to get MS Window settings
   application->PreInitApp();
   
   //Create the Windows class
   WNDCLASSEX winClass;

   winClass.cbSize = sizeof(WNDCLASSEX);
   winClass.style = CS_DBLCLKS | CS_OWNDC |
                    CS_HREDRAW | CS_VREDRAW;
   winClass.lpfnWndProc = WindowsMessageFunction;
   winClass.cbClsExtra = 0;
   winClass.cbWndExtra = 0;
   winClass.hInstance = hInstance;
   winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
   winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
   winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
   winClass.lpszMenuName = NULL;
   winClass.lpszClassName = "DxGuiFrameworkClass";
   winClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
   
   //Register the Windows class
   if(!RegisterClassEx(&winClass))
      return 0;

   if(!(application->hWnd = CreateWindow("DxGuiFrameworkClass",
      application->windowTitle, 
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      0, 0, 320, 200, NULL, NULL, hInstance, NULL)))
      return 0;

   //Allocate the global DGGraphics and DGInput objects
   //This must be done *after* the window is created
   dgGraphics = new DGGraphics();
   dgInput = new DGInput();

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
            {
               MessageBox(DGGetApp()->GetWindowsHandle(), outputText, 
                  "A DirectDraw Initialization Error Has Occurred", 
                  MB_OK | MB_ICONERROR);
               break;
            }

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