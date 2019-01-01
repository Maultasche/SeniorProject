/*------------------------------------------------------------------------
File Name: DxGuiFramework.h
Description: This file is the principal include file, which includes
   everything needed in the framework. To use the framework, simply
   include this file and link the library.
Version:
   1.0.0    10.02.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DXGUIFRAMEWORK_H
#define DXGUIFRAMEWORK_H

#pragma warning(disable:4786)

#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ddraw.h>
#include <stdio.h>
#include <fstream.h>
#include <map>

#include "DGDebugLog.h"
#include "DxGuiGlobals.h"
#include "DGException.h"
#include "DGLinkedList.h"
#include "DGQueue.h"
#include "DGSimpleClasses.h"
#include "DGColor.h"
#include "DGDisplayModeList.h"
#include "DGBitmap.h"
#include "DGBitmapList.h"
#include "DGFont.h"
#include "DGGraphics.h"
#include "DGSurface.h"
#include "DGInput.h"
#include "DGMessage.h"
#include "DGMessageLog.h"
#include "DGWindow.h"
#include "DGMainWindow.h"
#include "DGGUI.h"
#include "DGApplication.h"

//Global objects in the framework are declared here, 
extern DGGraphics* dgGraphics;
extern DGInput* dgInput;

//Global Functions
extern DGApplication* DGGetApp(void);
extern DGGraphics* DGGetGraphics(void);
extern DGGui* DGGetGui(void);

#endif