/*
	Date: June 24, 2011
	File Name: Queue.c
	Version: 1.03
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file contains all the code which comprises 
	the Queue library.  For method descriptions see
	Queue.h.
*/

#include "QueueConfig.h"
#include "Queue.h"

#if (USE_MALLOC == 1)
	#include "stdlib.h"
#endif // end of USE_MALLOC

QUEUE *CreateQueue(QUEUE *Queue, void (*CustomFreeMethod)(void *Data))
{
	QUEUE *TempQueue;

	// If the user didn't pass in a pointer, allocate memory for the QUEUE structure.
	if(QueueIsNull(Queue))
	{
		if((TempQueue = (QUEUE*)QueueMemAlloc(sizeof(QUEUE))) == (QUEUE*)NULL) // MemAlloc defined in QueueConfig.h
		{
			return (QUEUE*)NULL;
		}

		Queue = (QUEUE*)TempQueue;
	}

	// Initialize the Queue.
	Queue->Head = Queue->Tail = (QUEUE_NODE*)NULL;
	Queue->Size = (UINT32)0;

	#if(USING_QUEUE_DEPENDENT_FREE_METHOD == 1)
		Queue->QueueFreeMethod = (void(*)(void*))CustomFreeMethod;
	#endif // end of USING_QUEUE_DEPENDENT_FREE_METHOD

	return (QUEUE*)Queue;
}

BOOL QueueAdd(QUEUE *Queue, const void *Data)
{
	QUEUE_NODE *TempQueueNode;

	#if (QUEUE_SAFE_MODE == 1)
		if(QueueIsNull(Queue))
			return (BOOL)FALSE;
	#endif // end of QUEUE_SAFE_MODE

	// Allocate memory for the new node
	if((TempQueueNode = (QUEUE_NODE*)QueueMemAlloc(sizeof(QUEUE_NODE))) == (QUEUE_NODE*)NULL) // MemAlloc defined in QueueConfig.h
	{
		return (BOOL)FALSE;
	}

	// Initialize the new node.
	TempQueueNode->Data = (void*)Data;
	TempQueueNode->Next = (QUEUE_NODE*)NULL;

	/*
		Test for empty edge case, if so Tail and Head both point to the node.
		Otherwise just append it to the end of the QUEUE.
	*/
	if(QueueIsEmpty(Queue))
	{
		Queue->Head = Queue->Tail = (QUEUE_NODE*)TempQueueNode;
	}
	else
	{
		Queue->Tail->Next = (QUEUE_NODE*)TempQueueNode;
		Queue->Tail = (QUEUE_NODE*)TempQueueNode;
	}

	// Increment the size.
	Queue->Size++;

	return (BOOL)TRUE;
}

void *QueueRemove(QUEUE *Queue)
{
	void *Data;
	QUEUE_NODE *TempQueueNode;

	#if (QUEUE_SAFE_MODE == 1)
		if(QueueIsNull(Queue))
			return (void*)NULL;

		if(QueueIsEmpty(Queue))
			return (void*)NULL;
	#endif // end of QUEUE_SAFE_MODE

	// Set the temp node to the QUEUE's Head.
	TempQueueNode = (QUEUE_NODE*)(Queue->Head);

	// Iterate the QUEUE's Head to the next node (We don't know if it's NULL yet).
	Queue->Head = (QUEUE_NODE*)(Queue->Head->Next);

	// Get a handle on the data of the node we're about to remove.
	Data = (void*)(TempQueueNode->Data);

	// Free the old node.
	QueueMemDealloc(TempQueueNode); // MemDealloc defined in QueueConfig.h

	// Check to see if the Queue is now empty.
	if(Queue->Head == (QUEUE_NODE*)NULL)
		Queue->Tail = (QUEUE_NODE*)NULL;

	// No matter what, decrement the QUEUE's size by one.
	Queue->Size--;

	return (void*)Data;
}

#if (USING_QUEUE_PEEK_METHOD == 1)
	void *QueuePeek(QUEUE *Queue)
	{
		#if (QUEUE_SAFE_MODE == 1)
			if(QueueIsNull(Queue))
				return (void*)NULL;
	
			if(QueueIsEmpty(Queue))	
				return (void*)NULL;
		#endif // end of QUEUE_SAFE_MODE

		return (void*)(Queue->Head->Data);
	}
#endif // end of USING_QUEUE_PEEK_METHOD

#if (USING_QUEUE_CLEAR_METHOD == 1)
	BOOL QueueClear(QUEUE *Queue)
	{
		#if (QUEUE_SAFE_MODE == 1)
			if(QueueIsNull(Queue))
				return (BOOL)FALSE;
	
			if(QueueIsEmpty(Queue))
				return (BOOL)TRUE;
		#endif // end of QUEUE_SAFE_MODE

		while(Queue->Head != (QUEUE_NODE*)NULL)
		{
			// Iterate the Tail pointer to the node after the Head.
			Queue->Tail = (QUEUE_NODE*)(Queue->Head->Next);
	
			#if(USING_QUEUE_DEPENDENT_FREE_METHOD == 1)
				if(Queue->QueueFreeMethod)
				{
					Queue->QueueFreeMethod((void*)(Queue->Head->Data));
				}
			#endif // end of USING_QUEUE_DEPENDENT_FREE_METHOD
	
			QueueMemDealloc((void*)(Queue->Head)); // MemDealloc defined in QueueConfig.h

			// Iterate the Head to the Tail.
			Queue->Head = (QUEUE_NODE*)(Queue->Tail);
		}
	
		// The size is now 0 since the QUEUE is empty.
		Queue->Size = (UINT32)0;	

		return (BOOL)TRUE;
	}
#endif // end of USING_QUEUE_CLEAR_METHOD

#if (USING_QUEUE_GET_SIZE_METHOD == 1)
	UINT32 QueueGetSize(QUEUE *Queue)
	{
		#if (QUEUE_SAFE_MODE == 1)
			if(QueueIsNull(Queue))
				return (UINT32)0;
		#endif // end of QUEUE_SAFE_MODE

		return (UINT32)(Queue->Size);
	}
#endif // end of USING_QUEUE_GET_SIZE_METHOD

UINT32 QueueGetSizeInBytes(QUEUE *Queue, UINT32 DataSizeInBytes)
{
	UINT32 Size;

	#if (QUEUE_SAFE_MODE == 1)
		if(QueueIsNull(Queue))
			return (UINT32)0;
	#endif // end of QUEUE_SAFE_MODE

	Size = (UINT32)sizeof(QUEUE);

	if(QueueIsEmpty(Queue))
		return (UINT32)Size;

	/*
		If the user provided us with the size of their data in bytes
		then we must use it to calculate the size of the QUEUE in bytes.
		Otherwise we just don't include it in the calculation.
	*/
	if(DataSizeInBytes)
		Size += (Queue->Size * (DataSizeInBytes + (UINT32)sizeof(QUEUE_NODE)));
	else
		Size += (UINT32)(Queue->Size * (UINT32)sizeof(QUEUE_NODE));

	return (UINT32)Size;
}

#if (USING_QUEUE_GET_LIBRARY_VERSION == 1)

	const BYTE QueueLibraryVersion[] = {"Queue Lib v1.03\0"};
	
	const BYTE *QueueGetLibraryVersion(void)
	{
		return (const BYTE*)QueueLibraryVersion;
	}

#endif // end of USING_QUEUE_GET_LIBRARY_VERSION
