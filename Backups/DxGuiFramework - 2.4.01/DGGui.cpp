/*------------------------------------------------------------------------
File Name: DGGui.cpp
Description: This file contains the implementation of theDGGui class, 
   which represents the graphical user interface of the application 
   and manages windows and messages.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

/*Default Constructor*/
DGGui::DGGui()
{
   OutputDebugString("GUI constructor\n");
}

/*Destructor*/
DGGui::~DGGui()
{

}

/*------------------------------------------------------------------------
Function Name: SetMainWindow
Parameters:
   DGMainWindow mainWin : the pointer to the window to be made the main
      window
Description:
   This function receives a pointer to a window to be the main window
   and makes it the main window. If the window will be resized as
   necessary so that it covers the entire screen. The previous main
   window will be deleted.
------------------------------------------------------------------------*/

void DGGui::SetMainWindow(DGMainWindow* mainWin)
{

}

void DGGui::PostMessage(DGMessage* msg)
{

}

void DGGui::ProcessMessages(void)
{
   DGListIterator<DGWindow> listIterator(NULL, 0);
   listIterator++;
}


DGWindow* DGGui::GetWindow(UINT windowID)
{
   return NULL;
}

void DGGui::SetWindowFocus(UINT windowID)
{

}

UINT DGGui::GetWindowFocus()
{
   return 0;
}

void DGGui::RemoveWindowFocus()
{

}


void DGGui::DrawGUI()
{

}