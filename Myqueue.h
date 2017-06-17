/***********************************************************************//**
* @file
* @brief headerfile for the queue, contains the queue class and all related 
* functions
***************************************************************************/

#include <iostream>
using namespace std;
/**
* @brief the functions in the queue class
*/
#ifndef __MYQUEUE__H_
#define __MYQUEUE__H_
/**
* @brief A template class containing all the functions pertaining to the queue 
* we use to access/manipulate the boxes in the conveyer
*/

template <class TY>
class myqueue
{
	public:
		/*! the function used to construct the queue*/
		myqueue();					
		/*! the function used to copy the queue*/
		myqueue(myqueue<TY> &r);	
		/*! the function used to deconstruct the queue*/
		~myqueue();					
		/*! the function used to add an item to the queue*/
		bool enque(TY item);
		/*! the function used to take an item from the queue*/
		bool deque(TY &item);
		/*! the function used to see the last item in the queue i.e. the next 
		box to fall off of the conveyer*/
		bool front(TY &item);		
		/*! the function used to see if the queue is empty*/
		bool isEmpty();			
		/*! the function used to see how many items are in the queue i.e. how
		many boxes are in the conveyer*/
		int size();					
		/*! the struct portion of the nodes in the queue, holds the number of 
		the box and the pointer to the next box*/
private:						
		struct node
		{
			/*! the item portion of the nodes in the queue, holds the box 
			number*/
			TY item;			
			/*! the pointer portion of the nodes in the queue, points to the 
			next box */
			node *next;			
		};
		
		node *tailptr;	/*!<the tailptr node of the queue, the last box in the 
						circular queue */		
};
#endif
/**************************************************************************//*
*@author Hunter Comer
*
*@par Description
*sets tailptr to nullptr, creating the list
*
*
****************************************************************************/
template <class TY>
myqueue<TY>::myqueue()
{
	tailptr = nullptr;
}
/**************************************************************************//*
* @author Anne Voigt
* 
* @par Description
* initializes a new queue, takes each item from the old queue and copies it 
* piece by piece into the new queue, returning when you have reached the 
* tailptr of the old node. 
* 
* @param[in]	r   - the queue we are copying
* 
****************************************************************************/
template <class TY>
myqueue<TY>::myqueue(myqueue<TY> &r) 
{
	//initialize
	node *dest = nullptr, *src = nullptr;
	
	// make your tailptr point to nullptr (transfer to singly linked)
	tailptr = nullptr;
	// if the list is empty, return
	if (r.tailptr == nullptr)
		return;
	// set src to headptr
	src = r.tailptr->next;

	dest = new(nothrow)node;
	if (dest == nullptr)
		return;
	// set your dest to = whatever sourse headptr is

	dest->item = src->item;
	// traverse backwards to access tailptr
	dest->next = dest;
	//set the last dest as tailptr
	tailptr = dest;
	//if there was just one item , return now
	if (src->next == src)
		return;

	do
	{
		//traverse list
		src = src->next;
		//make tailptr->next a node
		tailptr->next = new(nothrow)node;
		//if its null, set instead to destination
		if (tailptr->next == nullptr)
		{
			tailptr->next = dest;
			return;
		}
		//traverse tailptr
		tailptr = tailptr->next;
		//whatever tailptr holds, put as source
		tailptr->item = src->item;
		//then traverse to dest
		tailptr->next = dest;
		//do while you arent at the end
	} while (src != r.tailptr);
}

/**************************************************************************//*
* @author Anne Voigt
* 
* @par Description
* Traverses through the queue to destruct each specific node until you reach 
* the end of the queue( make into singly linked list in order to reach end)
*
*
***************************************************************************/
template <class TY>
myqueue<TY>::~myqueue()
{
	// initialize nodes
	node *temp;
	node *h;
	// if the list is empty, youre done
	if (tailptr == nullptr)
		return;
	// else make temp the beginning of the linked list(it's circular)
	temp = tailptr->next;
	
	h = temp;
	// make it into a singly linked list once we have accessed the headptr
	tailptr->next = nullptr;
	// while we havent gone through the list
	while (temp != nullptr )
	{
		// go down the list, delete temp, and then traverse
		h = h->next;
		delete temp;
		temp = h;
	}
}
/*************************************************************************//*
* @author Hunter Comer
*
* @par Description
* checks to see if the queue is empty by seeing if tailptr is nullptr
* 
* @returns true if the queue is empty
*
****************************************************************************/
template <class TY>
bool myqueue<TY>::isEmpty() 
{
	//check if tailptr is equal to null (empty list)
	if (tailptr == nullptr)
		return true;

	return false;
}
/*************************************************************************//*
* @author Hunter Comer
*
* @par Description
* allows us to add an item to the queue by creating a new node and inserting 
* it behind tailptr, because it is a circular linked list
*
* @param[in] item - the item we want to insert into the queue
*
* @returns true if the item was successfully inserted
*
*****************************************************************************/
template <class TY>
bool myqueue<TY>::enque(TY item)   
{
	node *temp = nullptr;

	//create new node 
	temp = new (nothrow) node;
	if (temp == nullptr)
		return false;

	//put item into temp node
	temp->item = item;
	temp->next = nullptr;

	//if empty
	if (isEmpty())
	{
		tailptr = temp;
		tailptr->next = temp;
		return true;
	}
	//if not empty
	else
	{
		temp->next = tailptr->next;
		tailptr->next = temp;
		tailptr = temp;
		return true;
	}
}
/************************************************************************//*
* @author Garrett McIntosh
*
* @par Description
* allows us to deque an item from the list by returning false if empty, 
* deleting the last node, or by accessing the node in front of the one we
* want to delete, and then deleting the last node
*
* @param[out] item - the item we are taking out of the queue
*
* @returns true if the item was successfully dequed
*
***************************************************************************/
template <class TY>
bool myqueue<TY>::deque(TY &item)
{
	node * temp = nullptr;

	if (tailptr == nullptr)
		return false;

	item = tailptr->next->item;

	// handle deleting last node
	if (tailptr->next == tailptr)
	{
		delete tailptr;
		tailptr = nullptr;
		return true;
	}
	// not the last node in the list
	temp = tailptr->next;
	tailptr->next = temp->next;
	delete temp;

	return true;

}
/************************************************************************//*
* @author Jeremy Holwell
*
* @par Description
* allows us to check what the first box in the queue is, that is, the one that
* is about to fall off of the conveyer. Does so by returning false for empty 
* list, and then else returning the item number of the first  node
* 
* @param[out] item - the item at the front of the queue
*
* @returns true if there is an item in the list
*
****************************************************************************/
template <class TY>
bool myqueue<TY>::front(TY &item)  
{
	node *temp = nullptr;

	// handle empty list
	if (tailptr == nullptr)
		return false;

	item = tailptr->next->item;

	return true;
}

/************************************************************************//*
* @author Jeremy Holwell
*
* @par Description
* checks the size of the queue by returning false if the queue is empty, and 
* otherwise traversing and adding to count each traverse
*
* @returns size - how many items in the queue
*
****************************************************************************/
template <class TY>
int myqueue<TY>::size()
{
	node *temp = nullptr;
	int size = 0;

	//check for empty list
	if (tailptr == nullptr)
		return false;

	//set temp to tail
	temp = tailptr;
	//walk through list until end is reached
	do
	{
		temp = temp->next;
		size++;
	} while (temp != tailptr);

	return size;
}
