/*DisplayModeList.cpp*/

#include "DxGuiFramework.h"

/*------------------------------------------------------------------------
Function Name: DisplayModeSupported
Parameters:
   int width : the width of the display mode
   int height : the height of the display mode
   int colorDepth : the color depth(bit per pixel) of the display mode
Description:
   Receives a width, height, and color depth and returns whether the 
   display mode is in the list. If the display mode is in the list, it
   is supported by DirectDraw.
------------------------------------------------------------------------*/

bool DGDisplayModeList::DisplayModeSupported(int width, 
   int height, int colorDepth)
{
   //If the list is empty
   if(numOfItems == 0)
      return false;

   bool found = false;

   DGNode<DGDisplayMode>* nodePtr = first;
   for(int i = 0; i < numOfItems && !found; i++)
   {
      DGDisplayMode* displayMode = nodePtr->data;
      if(displayMode->width == width && displayMode->height == height &&
         displayMode->colorDepth == colorDepth)
         found = true;
      nodePtr = nodePtr->next;
   }

   return found;
}