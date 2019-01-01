/*------------------------------------------------------------------------
File Name: DGBitmap.cpp
Description: This file contains the implemenation of the DGGBitmap class. 
	An object of this class is able to load as well as store bitmaps.
Version:
   1.0.0    25.02.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"


/*Default Constructor*/
DGBitmapList::DGBitmapList() : DGLinkedList<DGBitmap>()
{
   highestPriority = 1;
   lowestPriority = 1;
   totalMemory = 0;
   numOfLoadedBitmaps = 0;
}

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   bool destroyItems : whether the data contained in the list is to be
      destroyed when the list is destroyed
------------------------------------------------------------------------*/

DGBitmapList::DGBitmapList(bool destroyItems) : 
      DGLinkedList<DGBitmap>(destroyItems)
{
   highestPriority = 1;
   lowestPriority = 1;
   totalMemory = 0;
   numOfLoadedBitmaps = 0;
}

/*------------------------------------------------------------------------
Function Name: RemoveFirstBitmapByPriority
Parameters:
   UINT priority : the priority of the bitmap to be removed
Description:
   This function iterates through the list of bitmaps and removes from 
   memory the first bitmap with the specified priority it encounters.
------------------------------------------------------------------------*/

void DGBitmapList::RemoveFirstBitmapByPriority(UINT priority)
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   bool done = false;

   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems && !done; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      if(bitmap->IsLoaded() &&
         bitmap->GetPriority() == priority)
      {
         bitmap->DestroyBitmap();
         done = true;
         numOfLoadedBitmaps--;
      }

      nodePtr = nodePtr->next;
   }

   UpdatePriorities();
}

/*------------------------------------------------------------------------
Function Name: RemoveAllBitmapsByPriority
Parameters:
   UINT priority : the priority of the bitmap to be removed
Description:
   This function iterates through the list of bitmaps, removing from 
   memory all bitmaps with the specified priority.
------------------------------------------------------------------------*/

void DGBitmapList::RemoveAllBitmapsByPriority(UINT priority)
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      if(bitmap->IsLoaded() &&
         bitmap->GetPriority() == priority)
      {
         bitmap->DestroyBitmap();
         numOfLoadedBitmaps--;
      }

      nodePtr = nodePtr->next;
   }

   UpdatePriorities();
}

/*------------------------------------------------------------------------
Function Name: RemoveFirstLowestPriorityBitmap
Parameters:
Description:
   This function iterates through the list of bitmaps and removes from 
   memory the first bitmap with the lowest priority it encounters.
------------------------------------------------------------------------*/

void DGBitmapList::RemoveFirstLowestPriorityBitmap()
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   bool done = false;

   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems && !done; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      if(bitmap->IsLoaded() &&
         bitmap->GetPriority() == lowestPriority)
      {
         bitmap->DestroyBitmap();
         done = true;
         numOfLoadedBitmaps--;
      }

      nodePtr = nodePtr->next;
   }

   UpdatePriorities();
}

/*------------------------------------------------------------------------
Function Name: RemoveAllLowestPriorityBitmaps
Parameters:
Description:
   This function iterates through the list of bitmaps, removing from 
   memory all bitmaps with the lowest priority.
------------------------------------------------------------------------*/

void DGBitmapList::RemoveAllLowestPriorityBitmaps()
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      if(bitmap->IsLoaded() &&
         bitmap->GetPriority() == lowestPriority)
      {
         bitmap->DestroyBitmap();
         numOfLoadedBitmaps--;
      }

      nodePtr = nodePtr->next;
   }

   UpdatePriorities();
}

/*------------------------------------------------------------------------
Function Name: RemoveAllBitmaps
Parameters:
Description:
   This function iterates through the list of bitmaps, removing
   each of the bitmaps from memory, but leaving the bitmap objects
   in the list.
------------------------------------------------------------------------*/

void DGBitmapList::RemoveAllBitmaps()
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      
      bitmap->DestroyBitmap();

      nodePtr = nodePtr->next;
   }

   numOfLoadedBitmaps = 0;
   highestPriority = 1;
   lowestPriority = 1;
}

/*------------------------------------------------------------------------
Function Name: RestoreBitmaps()
Parameters:
Description:
   This function iterates through the list of bitmaps, restoring their
   surfaces and reloading the bitmap.
------------------------------------------------------------------------*/

void DGBitmapList::RestoreBitmaps()
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      
      if(bitmap->IsLoaded())
         bitmap->RestoreBitmap();
         
      nodePtr = nodePtr->next;
   }
}

/*------------------------------------------------------------------------
Function Name: ProcessNewPriority
Parameters:
   UINT priority : the priority of the bitmap that is being added
Description:
   This function receives the priority of a bitmap that is being added
   to the list and updates the highest and lowest priorities if needed.
------------------------------------------------------------------------*/

void DGBitmapList::ProcessNewPriority(UINT priority)
{
   if(priority == 0)
      return;

   if(priority < highestPriority)
      highestPriority = priority;
   else
      lowestPriority = priority;
}

/*------------------------------------------------------------------------
Function Name: UpdatePriorities
Parameters:
Description:
   This function iterates through the list of bitmaps, updating the
   highest and lowest priorities. This function should be called if
   a bitmap is removed from the list.
------------------------------------------------------------------------*/

void DGBitmapList::UpdatePriorities()
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   highestPriority = 1;
   lowestPriority = 1;

   UINT priority;
   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      
      priority = bitmap->GetPriority();

      //We only look at those bitmaps who have a priority other than
      //0 and are loaded
      if(priority != 0 && bitmap->IsLoaded())
      {
         if(priority < highestPriority)
            highestPriority = priority;
         else if(priority > lowestPriority)
            lowestPriority = priority;
      }

      nodePtr = nodePtr->next;
   }
}

/*------------------------------------------------------------------------
Function Name: UpdateLoadedBitmaps
Parameters:
Description:
   This function iterates through the list of bitmaps, updating the
   number of loaded bitmaps. This function should be called if
   a bitmap is removed from the list.
------------------------------------------------------------------------*/

void DGBitmapList::UpdateLoadedBitmaps()
{
   //If the list is empty
   if(numOfItems == 0)
      return;

   numOfLoadedBitmaps = 0;

   DGNode<DGBitmap>* nodePtr = first;
   for(int i = 0; i < numOfItems; i++)
   {
      DGBitmap* bitmap = nodePtr->data;
      
      if(bitmap->IsLoaded())
         numOfLoadedBitmaps++;

      nodePtr = nodePtr->next;
   }
}

/*The following are just wrapper functions. They are overridden merely
  so the list can keep track of the lowest and highest priorities*/

void DGBitmapList::Insert(DGBitmap* data, int id)
{
   if(data->IsLoaded())
      numOfLoadedBitmaps++;
   DGLinkedList<DGBitmap>::Insert(data, id);
   ProcessNewPriority(data->GetPriority());
}

void DGBitmapList::Append(DGBitmap* data, int id)
{
   if(data->IsLoaded())
      numOfLoadedBitmaps++;
   DGLinkedList<DGBitmap>::Append(data, id);
   ProcessNewPriority(data->GetPriority());
}

void DGBitmapList::InsertAtPosition(int index, DGBitmap* data, int id)
{
   if(data->IsLoaded())
      numOfLoadedBitmaps++;
   DGLinkedList<DGBitmap>::InsertAtPosition(index, data, id);
   ProcessNewPriority(data->GetPriority());
}

void DGBitmapList::DeleteByIndex(int index)
{
   DGLinkedList<DGBitmap>::DeleteByIndex(index);
   UpdatePriorities();
   UpdateLoadedBitmaps();
}

void DGBitmapList::DeleteById(int id)
{
   DGLinkedList<DGBitmap>::DeleteById(id);
   UpdatePriorities();
   UpdateLoadedBitmaps();
}

void DGBitmapList::DeleteFirst()
{
   DGLinkedList<DGBitmap>::DeleteFirst();
   UpdatePriorities();
   UpdateLoadedBitmaps();
}

void DGBitmapList::DeleteLast()
{
   DGLinkedList<DGBitmap>::DeleteLast();
   UpdatePriorities();
   UpdateLoadedBitmaps();
}

void DGBitmapList::DeleteAll()
{
   DGLinkedList<DGBitmap>::DeleteAll();
   highestPriority = 1;
   lowestPriority = 1;
   totalMemory = 0;
   numOfLoadedBitmaps = 0;
}

DGBitmap* DGBitmapList::RemoveByIndex(int index)
{
   DGBitmap* bitmap = DGLinkedList<DGBitmap>::RemoveByIndex(index);
   UpdatePriorities();   
   if(bitmap->IsLoaded())
      numOfLoadedBitmaps--;
   return bitmap;
}

DGBitmap* DGBitmapList::RemoveById(int id)
{
   DGBitmap* bitmap = DGLinkedList<DGBitmap>::RemoveById(id);
   if(bitmap->IsLoaded())
      numOfLoadedBitmaps--;
   UpdatePriorities();   
   return bitmap;
}

DGBitmap* DGBitmapList::RemoveFirst()
{
   DGBitmap* bitmap = DGLinkedList<DGBitmap>::RemoveFirst();
   UpdatePriorities();
   if(bitmap->IsLoaded())
      numOfLoadedBitmaps--;
   return bitmap;
}

DGBitmap* DGBitmapList::RemoveLast()
{
   DGBitmap* bitmap = DGLinkedList<DGBitmap>::RemoveLast();
   UpdatePriorities();   
   if(bitmap->IsLoaded())
      numOfLoadedBitmaps--;
   return bitmap;
}

void DGBitmapList::RemoveAll()
{
   DGLinkedList<DGBitmap>::RemoveAll();
   highestPriority = 1;
   lowestPriority = 1;
   totalMemory = 0;
   numOfLoadedBitmaps = 0;
}