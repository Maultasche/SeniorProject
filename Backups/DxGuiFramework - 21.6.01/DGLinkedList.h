/*------------------------------------------------------------------------
File Name: DGLinkedList.h
Description: A templated linked list class
   Pointers to an item of the templated data type are stored in the 
   list and not the item itself
Version:
   1.0.0    18.12.2000  Created the file
   1.1.0    10.02.2001  Class Name changed from LinkedList to 
                        DGLinkedList. A default constructor was added.
------------------------------------------------------------------------*/

#ifndef DGLINKEDLIST_H
#define DGLINKEDLIST_H

#include <assert.h>

#define NO_ID  -1

template <class Data>
class DGNode
{
public:
   DGNode(int p_id, Data* p_data, DGNode* p_next)
   {
      id = p_id;
      data = p_data;
      next = p_next;
   }

   int id;
   Data* data;
   DGNode* next;
};

template <class Data>
class DGListIterator
{
public:
   //nodePtr is the node the iterator is to point to and
   //pos is the position in the list
   DGListIterator(DGNode<Data>* nodePtr, int pos)
   {
      currentNode = nodePtr;
      position = pos;
   }


   DGListIterator& operator++()
   {
      if(currentNode == NULL)
         return *this;
      else
      {
         currentNode = currentNode->next;
         position++;
      }

      return *this;
   }

   DGListIterator& operator++(int)
   {
      if(currentNode == NULL)
         return *this;
      else
      {
         currentNode = currentNode->next;
         position++;
      }

      return *this;
   }

   bool operator==(DGListIterator& iterator)
   {
      if(position == iterator.position && 
         currentNode == iterator.currentNode)
         return true;
      else
         return false;
   }
   //This returns true if the iterator has gone past the end of
   //the list or if the node pointer is NULL
   bool EndOfList(void)
   {
      if(currentNode == NULL)
         return true;
      else
         return false;
   }

   //This function assumes that the node pointed to by the 
   //iterator is valid
   Data* GetData(void)
   {
      assert(currentNode != NULL);
      return currentNode->data;
   }

   //This function assumes that the node pointed to by the 
   //iterator is valid
   int GetID(void)
   {
      assert(currentNode != NULL);
      return currentNode->id;
   }

   int GetPosition(void) {return position;}

private:
   DGNode<Data>* currentNode;
   int position;
};

template <class Data>
class DGLinkedList
{
public:
   DGLinkedList();
   DGLinkedList(bool destroyItems);
   virtual ~DGLinkedList();

   void SetDestroy(bool destroyItems) {destroy = destroyItems;}
   bool GetDestroy(void) {return destroy;}

   void Insert(Data* data, int id = NO_ID);
   void Append(Data* data, int id = NO_ID);
   void InsertAtPosition(int index, Data* data, int id = NO_ID);

   Data* GetItemByIndex(int index);
   Data* GetItemById(int id);
   Data* GetFirstItem(void);
   Data* GetLastItem(void);

   void DeleteByIndex(int index);
   void DeleteById(int id);
   void DeleteFirst(void);
   void DeleteLast(void);
   void DeleteAll(void);

   Data* RemoveByIndex(int index);
   Data* RemoveById(int id);
   Data* RemoveFirst(void);
   Data* RemoveLast(void);
   void RemoveAll(void);

   int GetNumOfItems(void) {return numOfItems;}

   DGListIterator<Data> Begin(void) 
   {return DGListIterator<Data>(first, 0);}

   DGListIterator<Data> End(void) 
   {return DGListIterator<Data>(NULL, numOfItems);}

   DGListIterator<Data> GetIterator(int index);

protected:
   DGNode<Data>* first;
   DGNode<Data>* last;

   int numOfItems;
   bool destroy;
};

/*------------------------------------------------------------------------
Function Name: DGLinkedList
Parameters:
Description:
   This is the DGLinkedList default class constructor. The default setting
   for the destroy area is true. The data is automatically set to be
   deleted when the object is destroyed.
------------------------------------------------------------------------*/
template <class Data>
DGLinkedList<Data>::DGLinkedList()
{
   numOfItems = 0;
   destroy = true;
   first = NULL;
   last = NULL;
}

/*------------------------------------------------------------------------
Function Name: DGLinkedList
Parameters:
   bool destroyItems : Tells the DGLinkedList object whether the contents 
   of the list should be deleted when the object is destroyed
Description:
   DGLinkedList class constructor
------------------------------------------------------------------------*/
template <class Data>
DGLinkedList<Data>::DGLinkedList(bool destroyItems)
{
   numOfItems = 0;
   destroy = destroyItems;
   first = NULL;
   last = NULL;
}

/*------------------------------------------------------------------------
Function Name: ~DGLinkedList
Parameters:
Description:
   DGLinkedList class destructor
------------------------------------------------------------------------*/
template <class Data>
DGLinkedList<Data>::~DGLinkedList()
{
   if(destroy)
      DeleteAll();
   else
      RemoveAll();
}

/*------------------------------------------------------------------------
Function Name: Insert
Parameters:
   Data* data : the data to be inserted
   int id : the id to give the data, defaults to NO_ID
Description:
   Inserts the given data item at the first position in the list
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::Insert(Data* data, int id)
{
   first = new DGNode<Data>(id, data, first);

   //If the list is empty
   if(last == NULL)
      last = first;

   numOfItems++;
}

/*------------------------------------------------------------------------
Function Name: Append
Parameters:
   Data* data : the data to be appended
   int id : the id to give the data, defaults to NO_ID
Description:
   Appends the given data item to the end of the list
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::Append(Data* data, int id)
{
   //If the list is empty
   if(last == NULL)
   {
      first = new DGNode<Data>(id, data, NULL);
      last = first;
   }

   //If the list already has nodes in it
   else
   {
      last->next = new DGNode<Data>(id, data, NULL);
      last = last->next;
   }

   numOfItems++;
}

/*------------------------------------------------------------------------
Function Name: InsertAtPosition
Parameters:
   int index : the index at which the data is inserted, index is 0-based
      The nodes that are already at or above that index will be moved up 
      one index. This function assumes that that data is being inserted 
      at an index that already exists or at the end of the list. 
      If index is equal to the number of items in the list, the data will 
      be appended to the end of the list. Any other nonexistant index will
      result in undefined behavior.
   Data* data : the data to be inserted
   int id : the id to give the data, defaults to NO_ID
Description:
   Inserts the given data at the specified index in the linked list
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::InsertAtPosition(int index, Data* data, int id)
{
   assert(index >= 0 && index <= numOfItems);

   //If the index is 0, Insert should have been called
   if(index == 0)
      Insert(data, id);

   //If index == numOfItems, append will be called
   else if(index == numOfItems)
      Append(data, id);

   else
   {
      DGNode<Data>* nodePtr = first;
      for(int i = 1; i < index; i++)
         nodePtr = nodePtr->next;

      nodePtr->next = new DGNode<Data>(id, data, nodePtr->next);

      numOfItems++;
   }
}

/*------------------------------------------------------------------------
Function Name: GetItemByIndex
Parameters:
   int index : the index of the item to retrieve, the index is assumed to
      be a valid index in the linked-list, index is 0-based
Description:
   Returns the data from the specified index in the linked list
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::GetItemByIndex(int index)
{
   assert(index >= 0 && index < numOfItems);

   DGNode<Data>* nodePtr = first;
   for(int i = 0; i < index; i++)
      nodePtr = nodePtr->next;

   return nodePtr->data;
}

/*------------------------------------------------------------------------
Function Name: GetItemById
Parameters:
   int id : the id associated with the item to be retrieved
Description:
   Returns the data of the first node in the linked list to have the
   given id or NULL if an item with the given id cannot be found.
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::GetItemById(int id)
{
   Data* data = NULL;
   DGNode<Data>* nodePtr = first;

   while(nodePtr != NULL && data == NULL)
   {
      if(nodePtr->id == id)
         data = nodePtr->data;

      else
         nodePtr = nodePtr->next;
   }

   return data;
}

/*------------------------------------------------------------------------
Function Name: GetFirstItem
Parameters:
Description:
   Returns the first data item in the list or NULL if the list is empty
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::GetFirstItem()
{
   Data* data = NULL;
   
   if(first != NULL)
      data = first->data;

   return data;
}

/*------------------------------------------------------------------------
Function Name: GetLastItem
Parameters:
Description:
   Returns the last data item in the list or NULL if the list is empty
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::GetLastItem()
{
   Data* data = NULL;
   
   if(last != NULL)
      data = last->data;

   return data;
}

/*------------------------------------------------------------------------
Function Name: DeleteByIndex
Parameters:
   int index : the index of the data item to be be deleted, it is assumed
      that this index exists
Description:
   The item at the specified index is removed and the data is deleted.
   It is assumed that the index is a valid index.
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::DeleteByIndex(int index)
{
   assert(index >= 0 && index < numOfItems);

   if(first == NULL)
      return;

   //DeleteFirst() should have been called
   if(index == 0)
      DeleteFirst();

   else
   {
      DGNode<Data>* nodePtr = first;
      DGNode<Data>* deletePtr;

      for(int i = 1; i < index; i++)
         nodePtr = nodePtr->next;

      deletePtr = nodePtr->next;
      if(nodePtr->next == last)
         last = nodePtr;

      nodePtr->next = nodePtr->next->next;
      delete deletePtr->data;
      delete deletePtr;
      numOfItems--;
   }
}

/*------------------------------------------------------------------------
Function Name: DeleteById
Parameters:
   int id : the id associated with the item to be deleted
Description:
   The data item associated with the specified id is removed from the
   list and deleted. If there is no item with the specified id, nothing
   is deleted.
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::DeleteById(int id)
{
   DGNode<Data>* deletePtr;

   if(first == NULL)
      return;

   //Check the first node
   if(first->id == id)
   {
      delete first->data;
      deletePtr = first;
      first = first->next;
      delete deletePtr;
      if(first == NULL)
         last = NULL;

      numOfItems--;
   }

   else if(first->next != NULL)
   {
      DGNode<Data>* nodePtr = first;
      bool nodeFound = false;
      while(!nodeFound && nodePtr->next != NULL)
      {
         if(nodePtr->next->id == id)
            nodeFound = true;

         else
            nodePtr = nodePtr->next;
      }
      
      if(nodeFound)
      {
         deletePtr = nodePtr->next;
         if(nodePtr->next == last)
            last = nodePtr;

         nodePtr->next = nodePtr->next->next;
         delete deletePtr->data;
         delete deletePtr;

         if(first == NULL)
            last = NULL;

         numOfItems--;
      }
   }
}

/*------------------------------------------------------------------------
Function Name: DeleteFirst
Parameters:
Description:
   The first data item in the list is removed from the list and deleted
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::DeleteFirst()
{
   if(first == NULL)
      return;

   DGNode<Data>* deletePtr = first;
   first = first->next;
   delete deletePtr->data;
   delete deletePtr;

   if(first == NULL)
      last = NULL;

   numOfItems--;
}

/*------------------------------------------------------------------------
Function Name: DeleteLast
Parameters:
Description:
   The last data item in the list is removed from the list and deleted
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::DeleteLast()
{
   DeleteByIndex(numOfItems - 1);
}

/*------------------------------------------------------------------------
Function Name: DeleteAll
Parameters:
Description:
   All data items in the list are removed from the list and deleted
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::DeleteAll()
{
   DGNode<Data>* deletePtr;
   while(first != NULL)
   {
      deletePtr = first;
      first = first->next;
      delete deletePtr->data;
      delete deletePtr;
   }

   last = NULL;
   numOfItems = 0;
}

/*------------------------------------------------------------------------
Function Name: RemoveByIndex
Parameters:
   int index : the index of the data item to be be removed, it is assumed
      that this index exists.
Description:
   The item at the specified index is removed. The data is *not*
   deleted and is returned. There should be a pointer to the data, 
   otherwise calling this function will cause a memory leak.
   If the list is empty, NULL is returned.
   It is assumed that the index is a valid index.
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::RemoveByIndex(int index)
{
   assert(index >= 0 && index < numOfItems);

   if(first == NULL)
      return NULL;

   Data* data = NULL;

   //RemoveFirst() should have been called
   if(index == 0)
      return RemoveFirst();

   else
   {
      DGNode<Data>* nodePtr = first;
      DGNode<Data>* deletePtr;

      for(int i = 1; i < index; i++)
         nodePtr = nodePtr->next;

      deletePtr = nodePtr->next;
      if(nodePtr->next == last)
         last = nodePtr;

      nodePtr->next = nodePtr->next->next;
      data = deletePtr->data;
      //Don't delete the data, just the node
      delete deletePtr;
      numOfItems--;
   }

   return data;
}

/*------------------------------------------------------------------------
Function Name: RemoveById
Parameters:
   int id : the id associated with the item to be removed
Description:
   The item associated with the specified id is removed from the
   list. The data is *not* deleted and is returned by the function. 
   There should be a pointer to the data, otherwise calling this 
   function will cause a memory leak.
   If there is no item with the specified id or the list is empty,
   NULL is returned.
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::RemoveById(int id)
{
   DGNode<Data>* deletePtr;

   if(first == NULL)
      return NULL;

   Data* data = NULL;
   //Check the first node
   if(first->id == id)
   {
      //Don't delete the data, just the node
      deletePtr = first;
      first = first->next;
      data = deletePtr->data;
      delete deletePtr;
      if(first == NULL)
         last = NULL;

      numOfItems--;
   }

   else if(first->next != NULL)
   {
      DGNode<Data>* nodePtr = first;
      bool nodeFound = false;
      while(!nodeFound && nodePtr->next != NULL)
      {
         if(nodePtr->next->id == id)
            nodeFound = true;

         else
            nodePtr = nodePtr->next;
      }
      
      if(nodeFound)
      {
         deletePtr = nodePtr->next;
         if(nodePtr->next == last)
            last = nodePtr;

         nodePtr->next = nodePtr->next->next;
         data = deletePtr->data;
         //Don't delete the data, just the node
         delete deletePtr;

         if(first == NULL)
            last = NULL;

         numOfItems--;
      }
   }

   return data;
}

/*------------------------------------------------------------------------
Function Name: RemoveFirst
Parameters:
Description:
   The first item in the list is removed from the list The data is
   *not* deleted and is returned by the function. There should be a 
   pointer to the data, otherwise calling this function will cause 
   a memory leak. If the list is empty, NULL is returned
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::RemoveFirst()
{
   if(first == NULL)
      return NULL;

   Data* data;
   DGNode<Data>* deletePtr = first;
   first = first->next;
   data = deletePtr->data;
   //Don't delete the data, just the node
   delete deletePtr;

   if(first == NULL)
      last = NULL;

   numOfItems--;

   return data;
}

/*------------------------------------------------------------------------
Function Name: DeleteLast
Parameters:
Description:
   The last item in the list is removed from the list. The data is
   *not* deleted, but is returned by the function. There should be 
   a pointer to the data, otherwise calling this function will cause a 
   memory leak. If the list is empty, NULL is returned
------------------------------------------------------------------------*/
template <class Data>
Data* DGLinkedList<Data>::RemoveLast()
{
   return RemoveByIndex(numOfItems - 1);
}

/*------------------------------------------------------------------------
Function Name: RemoveAll
Parameters:
Description:
   All items in the list are removed from the list, but the data is
   *not* deleted.  There should be another pointer to the data, 
   otherwise calling this function will cause a memory leak.
------------------------------------------------------------------------*/
template <class Data>
void DGLinkedList<Data>::RemoveAll()
{
   DGNode<Data>* deletePtr;
   while(first != NULL)
   {
      deletePtr = first;
      first = first->next;
      //Don't delete the data, just the node
      delete deletePtr;
   }

   last = NULL;
   numOfItems = 0;
}

/*------------------------------------------------------------------------
Function Name: GetIterator
Parameters:
   int index : the index for the iterator to point at
Description:
   This function returns an iterator that starts off pointing to the
   specified index.
------------------------------------------------------------------------*/
template <class Data>
DGListIterator<Data> DGLinkedList<Data>::GetIterator(int index) 
{
   assert(index >= 0 && index < numOfItems);

   DGNode<Data> node = first;
   for(int i = 0; i < index, i++)
      node = node->next;

   return DGListIterator<Data>(node, index);
}

#endif