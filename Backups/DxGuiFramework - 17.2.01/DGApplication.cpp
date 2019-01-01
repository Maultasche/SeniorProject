/*Application.cpp*/

#include "DxGuiFramework.h"

DGApplication::DGApplication(void)
{
   OutputDebugString("Application Constructor\n");

   mouseCursor = IDC_ARROW;
   strcpy(windowTitle, "DxGuiFramework Window");
   
   if(instance == NULL)
      instance = this;

   terminateApp = false;
}

DGApplication::~DGApplication(void)
{
   DestroyApp();
}

void DGApplication::PreInitApp(void)
{
   mouseCursor = IDC_ARROW;
   strcpy(windowTitle, "DxGuiFramework Window");
}

void DGApplication::InitApp(void)
{
   OutputDebugString("InitApp\n");
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
   
   while(!terminateApp)
   {
      HandleWindowsMessages();

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
   switch(uMsg)
   {
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

      default: break;
   }

   return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
