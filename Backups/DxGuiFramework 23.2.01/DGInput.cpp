/*------------------------------------------------------------------------
File Name: DGInput.cpp
Description: This file contains the implementation of the DGInput class, 
   which collects and stores input events, so that they can be passed on 
   to the GUI, which converts them into input messages.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

DGInput::DGInput()
{
   OutputDebugString("DGInput constructor\n");
}

DGInput::~DGInput()
{
   OutputDebugString("DGInput destructor\n");
}