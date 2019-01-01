/*Application.cpp*/

#include "DxGuiFramework.h"

DGApplication::DGApplication(void)
{
   OutputDebugString("Application Constructor\n");

   if(instance == NULL)
      instance = this;

   terminateApp = false;

   //Default window class settings
   windowClass.cbSize = sizeof(WNDCLASSEX);
   windowClass.style = CS_DBLCLKS | CS_OWNDC |
                    CS_HREDRAW | CS_VREDRAW;
   windowClass.cbClsExtra = 0;
   windowClass.cbWndExtra = 0;
   windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
   windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
   windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
   windowClass.lpszMenuName = NULL;
   windowClass.lpszClassName = "DxGuiFrameworkClass";
   windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

   strcpy(windowSettings.windowName, "DxGui Application Window");
   windowSettings.dwStyle = WS_POPUP | WS_VISIBLE;
   windowSettings.xPos = 0;
   windowSettings.yPos = 0;
   windowSettings.nWidth = GetSystemMetrics(SM_CXSCREEN);
   windowSettings.nHeight = GetSystemMetrics(SM_CYSCREEN);
   windowSettings.hMenu = NULL;
}

DGApplication::~DGApplication(void)
{
   DestroyApp();
}

void DGApplication::PreInitApp(void)
{

}

void DGApplication::InitApp(void)
{
   OutputDebugString("InitApp\n");
   dgGraphics->SetGraphicsMode(DGPoint(640, 480), WS_WINDOWED,
      CD_16BIT);
}

void DGApplication::DestroyApp(void)
{

}
   
void DGApplication::TerminateApp(void)
{
   terminateApp = true;
   OutputDebugString("TerminateApp\n");
}

void DGApplication::RunApp(void)
{
   OutputDebugString("RunApp\n");
   //int startTime;
   while(!terminateApp)
   {
      HandleWindowsMessages();
 
      //If the application is not active, don't update anything
      if(appActive)
      {
         dgGraphics->BeginFrame();

         PreGUIMessage();

         //Have gui generate, dispatch, and handle messages

         PreGUIDraw();

         //Have gui draw itself

         PostGUIDraw();

         dgGraphics->EndFrame();

         //If there is still time, call OnIdle()
      }

      else
         Sleep(0);
   }
}

void DGApplication::PreGUIMessage(void)
{

}

void DGApplication::PreGUIDraw(void)
{

}

void DGApplication::PostGUIDraw(void)
{

}

void DGApplication::HandleWindowsMessages()
{
   MSG msg;

   while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

}

LRESULT DGApplication::WindowsMessageFunction(HWND hWnd, 
   UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   RECT clientRect;

   //Check to see if we need to activate or deactivate the 
   //application.
   if(uMsg == WM_ACTIVATE)
   {
      //If the window is minimized, the application is deactivated
      if(HIWORD(wParam) == TRUE)
      {
         OutputDebugString("Application disabled\n");
         appActive = false;
      }
      else
      {
         OutputDebugString("Application enabled\n");
         appActive = true;
      }
   }

   //We don't want to have any messages passed to the GUI when
   //the application is inactive
   if(!appActive)
      return DefWindowProc(hWnd, uMsg, wParam, lParam);

   switch(uMsg)
   {
      case WM_ACTIVATE:
      {
         //Update the client rectangle info
         if(dgGraphics != NULL)
         {
            GetClientRect(hWnd, &clientRect);
            ClientToScreen(hWnd, (LPPOINT)&clientRect );
            ClientToScreen(hWnd, (LPPOINT)&clientRect + 1 );
            dgGraphics->SetClientRect(clientRect);
         }
         break;
      }
      case WM_MOVE:
      {
         //Update the client rectangle info
         if(dgGraphics != NULL)
         {
            GetClientRect(hWnd, &clientRect);
            ClientToScreen(hWnd, (LPPOINT)&clientRect );
            ClientToScreen(hWnd, (LPPOINT)&clientRect + 1 );
            dgGraphics->SetClientRect(clientRect);
         }
         break;
      }
      case WM_SIZE:
      {
         //Update the client rectangle info
         if(dgGraphics != NULL)
         {
            GetClientRect(hWnd, &clientRect);
            ClientToScreen(hWnd, (LPPOINT)&clientRect );
            ClientToScreen(hWnd, (LPPOINT)&clientRect + 1 );
            dgGraphics->SetClientRect(clientRect);
         }
         break;
      }
      case WM_DESTROY: 
      {
         TerminateApp();
         break;
      }

      case WM_QUIT: 
      {
         TerminateApp();
         break;
      }

      case WM_KEYDOWN:
      {
         switch (wParam)
         {
            case VK_ESCAPE:
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            return 0;
         }
         break;
      }

      case WM_LBUTTONDBLCLK:
      {
         TerminateApp();
         break;     
      }

      case WM_RBUTTONUP:
      {
         if(dgGraphics->GetWindowedState() == WS_WINDOWED)
            dgGraphics->SetGraphicsMode(DGPoint(640, 480), 
               WS_FULLSCREEN, CD_32BIT, BT_DOUBLE, true);
         else
             dgGraphics->SetGraphicsMode(DGPoint(640, 480), 
               WS_WINDOWED, CD_32BIT, BT_SINGLE, true);
         break;
      }
      default: break;
   }

   return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
