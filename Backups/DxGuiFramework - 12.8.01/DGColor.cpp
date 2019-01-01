/*------------------------------------------------------------------------
File Name: DGColor.cpp
Description: This file contains the implementation of the DGColor class, 
   which is used to store a standard pixel format. DGColor can convert 
   its standard color format into pixel formats matching the current pixel
   format and color depth.
Version:
   1.0.0    20.06.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

//Initialize the static variables
USHORT* DGColor::red16BitTable = NULL;
USHORT* DGColor::green16BitTable = NULL;
USHORT* DGColor::blue16BitTable = NULL;

UINT* DGColor::red24BitTable = NULL;
UINT* DGColor::green24BitTable = NULL;
UINT* DGColor::blue24BitTable = NULL;

UINT* DGColor::red32BitTable = NULL;
UINT* DGColor::green32BitTable = NULL;
UINT* DGColor::blue32BitTable = NULL;

//Function to create the static pixel format lookup tables,
//It is assumed that colorDepth is either CD_16BIT, CD_24BIT, or CD_32BIT
void DGColor::CreateLookupTables(DDPIXELFORMAT& pixelFormat, UINT colorDepth)
{
   assert(colorDepth == CD_16BIT || colorDepth == CD_24BIT || 
          colorDepth == CD_32BIT);

   //Delete any previous lookup tables and set them to NULL
   if(red16BitTable != NULL)
      delete red16BitTable;
   if(green16BitTable != NULL)
      delete green16BitTable;
   if(blue16BitTable != NULL)
      delete blue16BitTable;

   if(red24BitTable != NULL)
      delete red24BitTable;
   if(green24BitTable != NULL)
      delete green24BitTable;
   if(blue24BitTable != NULL)
      delete blue24BitTable;

   if(red32BitTable != NULL)
      delete red32BitTable;
   if(green32BitTable != NULL)
      delete green32BitTable;
   if(blue32BitTable != NULL)
      delete blue32BitTable;

   red16BitTable = green16BitTable = blue16BitTable = NULL;
   red24BitTable = green24BitTable = blue24BitTable = NULL;
   red32BitTable = green32BitTable = blue32BitTable = NULL;

   switch(colorDepth)
   {
      case CD_16BIT:
         red16BitTable = new USHORT[256];
         green16BitTable = new USHORT[256];
         blue16BitTable = new USHORT[256];

         Create16BitLookupTable(pixelFormat.dwRBitMask, red16BitTable);
         Create16BitLookupTable(pixelFormat.dwGBitMask, green16BitTable);
         Create16BitLookupTable(pixelFormat.dwBBitMask, blue16BitTable);
         break;
      case CD_24BIT:
         red24BitTable = new UINT[256];
         green24BitTable = new UINT[256];
         blue24BitTable = new UINT[256];

         Create24Or32BitLookupTable(pixelFormat.dwRBitMask, red24BitTable);
         Create24Or32BitLookupTable(pixelFormat.dwGBitMask, green24BitTable);
         Create24Or32BitLookupTable(pixelFormat.dwBBitMask, blue24BitTable);
         break;
      case CD_32BIT:
         red32BitTable = new UINT[256];
         green32BitTable = new UINT[256];
         blue32BitTable = new UINT[256];

         Create24Or32BitLookupTable(pixelFormat.dwRBitMask, red32BitTable);
         Create24Or32BitLookupTable(pixelFormat.dwGBitMask, green32BitTable);
         Create24Or32BitLookupTable(pixelFormat.dwBBitMask, blue32BitTable);
         break;
   }
}

//Creates a lookup table based on bitMask, it is assumed that luTable
//is a pointer to an array of size 256, this function can be used
//for 16-bit color depth only
void DGColor::Create16BitLookupTable(DWORD bitMask, USHORT* luTable)
{
   assert(luTable != NULL);

   for(int i = 0; i < 256; i++)
      luTable[i] = USHORT(((i * __int64(bitMask)) / 255) & bitMask);
}

//Creates a lookup table based on bitMask, it is assumed that luTable
//is a pointer to an array of size 256, this function can be used
//for 24- or 32-bit color depths (since there is no 24-bit data type)
void DGColor::Create24Or32BitLookupTable(DWORD bitMask, UINT* luTable)
{
   assert(luTable != NULL);

   for(int i = 0; i < 256; i++)
      luTable[i] = UINT(((i * __int64(bitMask)) / 255) & bitMask);
}
