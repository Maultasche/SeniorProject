/*------------------------------------------------------------------------
File Name: DxGuiGlobals.h
Description: This file contains all the global definitions and macros
   that are needed throughout the DirectX GUI framework.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/


#ifndef DXGUIGLOBALS_H
#define DXGUIGLOBALS_H

//GUI message definitions
#define  GM_NONE              0        
#define  GM_FOCUS             1
#define  GM_LOSEFOCUS         2
#define  GM_LBUTTONDOWN       3
#define  GM_LBUTTONUP         4
#define  GM_LBUTTONDBLCLK     5
#define  GM_MBUTTONDOWN       6
#define  GM_MBUTTONUP         7
#define  GM_MBUTTONDBLCLK     8
#define  GM_RBUTTONDOWN       9
#define  GM_RBUTTONUP         10
#define  GM_RBUTTONDBKCLK     11
#define  GM_MOUSEENTER        12
#define  GM_MOUSELEAVE        13
#define  GM_KEYDOWN           14
#define  GM_KEYUP             15
#define  GM_KEYPRESSED        15
#define  GM_MOVING            16
#define  GM_MOVED             17
#define  GM_REPOSITION        18
#define  GM_SIZING            19
#define  GM_SIZED             20
#define  GM_RESIZE            21
#define  GM_SHOWWINDOW        22
#define  GM_HIDEWINDOW        23
#define  GM_DISPLAYCHANGE     24
#define  GM_CREATE            25
#define  GM_DESTROY           26

//WindowType Definitions
#define  WT_GENERICWINDOW     0
#define  WT_MAINWINDOW        1

//Data Type Definitions
typedef void (*MsgHandlerFunction)(...);

//Buffering Definitions
#define  BT_SINGLE            1
#define  BT_DOUBLE            2
#define  BT_TRIPLE            3

//Windowed State Definitions
#define  WS_WINDOWED          1
#define  WS_FULLSCREEN        2

//Color Depth Definitions
#define  CD_8BIT              1
#define  CD_16BIT             2
#define  CD_24BIT             3
#define  CD_32BIT             4
#define  CD_16BIT5            5
#define  CD_16BIT6            6

//Bitmap ID Definitions
#define  IDB_NO_ID            0

//Exception Definitions
//Error Codes

#define  EC_UNKNOWN           0
#define  EC_DDINIT            1
#define  EC_DDSETGRAPHMODE    2
#define  EC_DDLOCKSURFACE     3
#define  EC_DDUNLOCKSURFACE   4
#define  EC_DDFLIPSURFACE     5
#define  EC_DDRESTORESURFACES 6
#define  EC_DDFILLSCREEN      7
#define  EC_DDCLEARPRIMARY    8

#define  EC_BMBITMAPSIZE      1
#define  EC_BMBITMAPLOAD      2

//Error Types

#define  ET_UNKNOWN           0
#define  ET_DIRECTDRAW        1
#define  ET_BITMAP            2

//Name Substitution Defines
#define  FC   __fastcall

#endif