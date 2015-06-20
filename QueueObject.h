/*
	Date: June 24, 2011
	File Name: QueueObject.h
	Version: 1.03
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file contains the definition of the QUEUE
	data structure.  This file was created just to 
	further seperate out the structure of the library.
*/

#ifndef QUEUE_OBJECT_H
	#define QUEUE_OBJECT_H

#include "GenericTypeDefs.h"

/*
	The following struct is a node within the Queue.
	Each node points to a piece of data that the user
	passed in when calling QueueAdd().
*/
struct _QueueNode
{
	/**
	* A pointer to the data that the QUEUE_NODE will point to.
	*/
	void *Data;

	/**
	* A pointer to the next QUEUE_NODE in the QUEUE.
	*/
	struct _QueueNode *Next;
};

typedef struct _QueueNode QUEUE_NODE;

/*
	The following struct is the Queue Head itself.
	There is only one of these per Queue, and it points
	to the beginning and end of the Queue (the first and last
	QUEUE_NODE).
*/
struct _Queue
{
	/**
	* The current size of a QUEUE.  When initialized a QUEUE has a size of 0.
	*/
	UINT32 Size;

	/**
	* A pointer to the beginning of the QUEUE.  The data at this Node is the next
	to be returned by QueueRemove() or QueuePeek().
	*/
	QUEUE_NODE *Head;

	/**
	* A pointer to the end of the QUEUE.  The next Node to be added to the QUEUE
	will be placed after the Node that this pointing to.
	*/
	QUEUE_NODE *Tail;

	#if(USING_QUEUE_DEPENDENT_FREE_METHOD == 1)
		void (*QueueFreeMethod)(void *Data);
	#endif // end of USING_QUEUE_DEPENDENT_FREE_METHOD
};

typedef struct _Queue QUEUE;

#endif // end of QUEUE_OBJECT_H
