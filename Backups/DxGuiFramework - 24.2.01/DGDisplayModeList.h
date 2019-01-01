/*------------------------------------------------------------------------
File Name: DGDisplayModeList.h
Description: This file contains a derivation of DGLinkedList that is used
	to store display mode enumerations.
Version:
   1.0.0    17.02.2000  Created the file
------------------------------------------------------------------------*/

#ifndef DGDISPLAYMODE_H
#define DGDISPLAYMODE_H

class DGDisplayMode
{
public:
   int width;
   int height;
   int colorDepth;

   DGDisplayMode(int w, int h, int clrDepth)
   {
      width = w;
      height = h;
      colorDepth = clrDepth;
   }

};

class DGDisplayModeList : public DGLinkedList<DGDisplayMode>
{
public:
   //Constructor: destroyItems specifies whether the data 
   //in the queue should be deleted when the queue is destroyed
   DGDisplayModeList(bool destroyItems) : 
      DGLinkedList<DGDisplayMode>(destroyItems) {}
   DGDisplayModeList() : DGLinkedList<DGDisplayMode>() {}

   //Destructor
   ~DGDisplayModeList() {}

   bool DisplayModeSupported(int width, int height, int colorDepth);
};

#endif