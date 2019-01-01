/*------------------------------------------------------------------------
File Name: DGBitmapList.h
Description: This file contains a derivation of DGLinkedList that is used
	to store and manage bitmaps.
Version:
   1.0.0    25.02.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGBITMAPLIST_H
#define DGBITMAPLIST_H

class DGBitmapList : public DGLinkedList<DGBitmap>
{
public:
   //Constructor: destroyItems specifies whether the data 
   //in the queue should be deleted when the queue is destroyed
   DGBitmapList(bool destroyItems);
   DGBitmapList();

   //Destructor
   ~DGBitmapList() {}

   //Wrapper Functions
   void Insert(DGBitmap* data, int id = NO_ID);
   void Append(DGBitmap* data, int id = NO_ID);
   void InsertAtPosition(int index, DGBitmap* data, int id = NO_ID);

   void DeleteByIndex(int index);
   void DeleteById(int id);
   void DeleteFirst(void);
   void DeleteLast(void);
   void DeleteAll(void);

   DGBitmap* RemoveByIndex(int index);
   DGBitmap* RemoveById(int id);
   DGBitmap* RemoveFirst(void);
   DGBitmap* RemoveLast(void);
   void RemoveAll(void);

   //Real Functions
   void RemoveFirstBitmapByPriority(UINT priority);
   void RemoveAllBitmapsByPriority(UINT priority);
   void RemoveFirstLowestPriorityBitmap(void);
   void RemoveAllLowestPriorityBitmaps(void);
   void RemoveAllBitmaps(void);
   void RestoreBitmaps(void);

   UINT GetHighestPriority(void) {return highestPriority;}
   UINT GetLowestPriority(void) {return lowestPriority;}
   UINT GetTotalMemory(void) {return totalMemory;}
   UINT GetNumOfLoadedBitmaps(void) {return numOfLoadedBitmaps;}

private:
   void ProcessNewPriority(UINT priority);
   void UpdatePriorities(void);
   void UpdateLoadedBitmaps(void);

   UINT highestPriority;
   UINT lowestPriority;
   UINT numOfLoadedBitmaps;
   UINT totalMemory;
};

#endif