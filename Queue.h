/*
	Date: June 24, 2011
	File Name: Queue.h
	Version: 1.03
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file allows the user to utilize the QUEUE data
	structure.  It provides all necessary method headers for 
	accessing the Queue library.  The library is configurable
	with the use of QueueConfig.h.  This file must be included
	in every file that references the Queue library or
	QUEUE data structure.

	All methods are callable to the user.
*/

/*! \mainpage Queue Library
 *  \brief This is a Library written in C for manipulating a Queue Data Structure.
 *  \author brodie
 *  \version 1.03
 *  \date   April 4, 2011
 */

#ifndef QUEUE_H
	#define QUEUE_H

#include "QueueConfig.h"
#include "QueueObject.h"
#include "GenericTypeDefs.h"

/*
	Function: QUEUE *CreateQueue(QUEUE *Queue)

	Parameters: 
		QUEUE *Queue - The address at which the QUEUE will be inititalized.
		If NULL is passed in then this method will create a QUEUE out of a
		the heap with a call to QueueMemAlloc()(User Supplied Define).

	Returns:
		QUEUE* - The address at which the newly initialized QUEUE resides
		in memory.  If a new QUEUE could not be created then (QUEUE*)NULL is returned.

	Description: Creates a new QUEUE in memory.

	Notes: If the call to QueueMemAlloc() fails then this method will call
	SystemHeapOutOfMemoryException() which must be implemented by the user.
*/
/**
		* @brief Initializes a QUEUE, and can create a QUEUE.
		* @param *Queue - A pointer to an already allocate QUEUE or a NULL QUEUE 
		pointer to create a QUEUE from QueueMemAlloc().
		* @return *QUEUE - The address of the QUEUE in memory.  If a QUEUE could
		not be allocated, returns a NULL QUEUE pointer.
		* @note If the call to QueueMemAlloc() fails then this method will call
		SystemHeapOutOfMemoryException() which must be implemented by the 
		user.
		* @sa SystemHeapOutOfMemoryException(), QueueMemAlloc()
		* @since v1.0
*/
QUEUE *CreateQueue(QUEUE *Queue, void (*CustomFreeMethod)(void *Data));

/*
	Function: BOOL QueueAdd(QUEUE *Queue, const void *Data)

	Parameters: 
		QUEUE *Queue - The address at which the QUEUE resides in memory.
		const void *Data - The data to store at the end of the QUEUE.

	Returns:
		BOOL - Will return TRUE if the const void *Data was successfully
		stored in the QUEUE. Will return FALSE if the QUEUE pointer was
		NULL or if there is no more room in the heap to allocate for a new
		item on the QUEUE.

	Description: Pushes one item onto the QUEUE.

	Notes: If the call to QueueMemAlloc() fails then this method will call
	SystemHeapOutOfMemoryException() which must be implemented by the user.
*/
/**
		* @brief Puts a new QUEUE_NODE with it's accompanying data at the end of the QUEUE.
		* @param *Queue - The address at which the QUEUE resides in memory.
		* @param *Data \a- A void pointer to the address at which the data that 
		will be put into the QUEUE resides at.
		* @return BOOL - TRUE if the operation was successful.  FALSE if there 
		was not enough memory to add a QUEUE_NODE.
		* @note This method will allocate a new QUEUE_NODE through a call to QueueMemAlloc().
		If QueueMemAlloc() fails this method will call SystemHeapOutOfMemoryException() 
		which must be implemented by the user.
		* @sa SystemHeapOutOfMemoryException(), QueueMemAlloc()
		* @since v1.0
*/
BOOL QueueAdd(QUEUE *Queue, const void *Data);

/*
	Function: void *QueueRemove(QUEUE *Queue)

	Parameters: 
		QUEUE *Queue - The address at which the QUEUE resides in memory.

	Returns:
		void* - The data of the next item that was removed from the QUEUE.  
		If no items are available or if the Queue is a NULL reference
		then this method returns (void*)NULL.

	Description: Removes one item from the beginning of the QUEUE.  That 
	item is no longer in the QUEUE.  It is the users responsibility to free 
	any memory which the returned void pointer is pointing to if necessary.

	Notes: None
*/
/**
		* @brief Removes and returns the next set of data on top of the QUEUE.
		* @param *Queue - The address at which the Queue resides in memory.
		* @return *void - The address in memory of the top QUEUE_NODE in the 
		passed in QUEUE, or (void*)NULL if unsuccessful.  The QUEUE_NODE 
		is torn down from memory with QueueMemDealloc().
		* @note This method will free the top QUEUE_NODE with a call to QueueMemDealloc().
		* @sa QueueMemDealloc()
		* @since v1.0
*/
void *QueueRemove(QUEUE *Queue);

/*
	Function: void *QueuePeek(QUEUE *Queue)

	Parameters: 
		QUEUE *Queue - The address at which the QUEUE resides in memory.

	Returns:
		void* - The data of the next item to be removed from the QUEUE.  
		If no items are available or if the Queue is NULL then this 
		method returns NULL.  The node which holds the returned data still
		resides in the QUEUE.

	Description: Returns but does not delete the next piece of data in the
	QUEUE.

	Notes: USING_QUEUE_PEEK_METHOD must be defined as 1 in QueueConfig.h to use method.
*/
/**
		* @brief Returns the next set of data on top of the QUEUE.
		* @param *Queue - The address at which the QUEUE resides in memory.
		* @return void* - The address of the next piece of data on top of the QUEUE, 
		or (void*)NULL if unsuccessful.
		* @note This method will return but not remove from the QUEUE, the next 
		set of data at the beginning of the QUEUE.  USING_QUEUE_PEEK_METHOD must be 
		defined as 1 in QueueConfig.h to use method.
		* @sa None
		* @since v1.0
*/
#if (USING_QUEUE_PEEK_METHOD == 1)
	void *QueuePeek(QUEUE *Queue);
#endif // end of USING_QUEUE_PEEK_METHOD

/*
	Function: BOOL QueueClear(QUEUE *Queue)

	Parameters: 
		QUEUE *Queue - The address at which the QUEUE resides in memory.

	Returns:
		BOOL - TRUE if the QUEUE was successfully torn down out of memory, or it
			   the Queue had a size of 0.
		FALSE - If a NULL referenced QUEUE was passed in.

	Description: This method will free up all the memory used up by the
	QUEUE_NODE's within the QUEUE.  This will not free the QUEUE and will
	not free the data being pointed to by each node within the QUEUE unless
	FreeAll is set to TRUE.

	Notes: USING_QUEUE_CLEAR_METHOD must be defined as 1 in QueueConfig.h to use method.
*/
/**
		* @brief Frees from memory all of a QUEUE's nodes and data(optional).
		* @param *Queue - The address at which the QUEUE resides in memory.
		* @return BOOL - TRUE if all the QUEUE_NODE's and data was successfully freed,
		FALSE otherwise.
		* @note This method frees all the Nodes within a QUEUE.  If the user wishes to
		free all the data pointed to by each node then a user supplied method at the
		Queues creation should be done.  USING_QUEUE_CLEAR_METHOD must be defined as 
		1 in QueueConfig.h to use method.
		* @sa QueueMemDealloc(), CreateQueue()
		* @since v1.0
*/
#if (USING_QUEUE_CLEAR_METHOD == 1)
	BOOL QueueClear(QUEUE *Queue);
#endif // end of USING_QUEUE_CLEAR_METHOD

/*
	Function: UINT32 QueueGetSize(QUEUE *Queue)

	Parameters: 
		QUEUE *Queue - The address at which the QUEUE resides in memory.

	Returns:
		UINT32 - The number of elements currently found in the QUEUE 
		passed in.  If the QUEUE referenced is NULL then this method will 
		return 0.

	Description: Returns the size of the referenced QUEUE.

	Notes: USING_QUEUE_GET_SIZE_METHOD must be defined as 1 in QueueConfig.h to use method.
*/
/**
		* @brief Will return the number of QUEUE_NODES within a QUEUE.
		* @param *Queue - The address at which the QUEUE resides in memory.
		* @return UINT32 - The number of QUEUE_NODE's in the QUEUE.  
		If the Queue is eqaul to (QUEUE*)NULL then 0 is returned.
		* @note USING_QUEUE_GET_SIZE_METHOD must be defined as 1 in QueueConfig.h to use method.
		* @sa None
		* @since v1.0
*/
#if (USING_QUEUE_GET_SIZE_METHOD == 1)
	UINT32 QueueGetSize(QUEUE *Queue);
#endif // end of USING_QUEUE_GET_SIZE_METHOD

/*
	Function: UINT32 QueueGetSizeInBytes(QUEUE *Queue, UINT32 DataSizeInBytes)

	Parameters: 
		QUEUE *Queue - The address at which the QUEUE resides in memory.
		UINT32 DataSizeInBytes - The size in bytes of the data being stored
								 at each QUEUE_NODE for the referenced QUEUE.

	Returns:
		UINT32 - The size in bytes that the entire QUEUE Data Structure takes up.  This
		takes into account the size of each QUEUE_NODE within the QUEUE, the size of a 
		QUEUE and the size of each data element a QUEUE_NODE is pointing to.  If the user
		is not pointing to anything with the QUEUE_NODES's then DataSizeInBytes should be 
		set to 0.  If the QUEUE referenced is NULL then this method will return 0.

	Description: Returns the size of the referenced QUEUE in bytes.

	Notes: This method does not take into account how much memory is used to allocate 
	memory through QueueMemAlloc().  USING_QUEUE_GET_SIZE_IN_BYTES_METHOD must be defined as
	1 in QueueConfig.h to use method
*/
/**
		* @brief Returns how much memory in bytes a QUEUE consumes.
		* @param *Queue - The address at which the QUEUE resides in memory.
		* @param DataSizeInBytes - The size in bytes of the data being stored 
		at each QUEUE_NODE for the referenced QUEUE.  Should be 0 if the data
		in each QUEUE_NODE is not used as a pointer.
		* @return UINT32 - Returns the size of the referenced QUEUE in bytes.  Will
		return 0 if unsuccessful.
		* @note This method will take into account the sizeof QUEUE, plus
		the size of each QUEUE_NODE.  This method will not take into account
		the amount of memory needed to allocate memory from QueueMemAlloc().
		USING_QUEUE_GET_SIZE_IN_BYTES_METHOD must be defined as 1 in QueueConfig.h to use method.
		* @sa must be defined as 1 in QueueConfig.h to use method.
		* @since v1.0
*/
#if (USING_QUEUE_GET_SIZE_IN_BYTES_METHOD == 1)
	UINT32 QueueGetSizeInBytes(QUEUE *Queue, UINT32 DataSizeInBytes);
#endif // end of USING_QUEUE_GET_SIZE_IN_BYTES_METHOD

/*
	Function: const BYTE *QueueGetLibraryVersion(void)

	Parameters: 
		None

	Returns:
		const BYTE* - The current version of the Queue Library.  This string is 
		(BYTE)NULL terminated.

	Description: Returns the current version of the Queue Library.

	Notes: USING_QUEUE_GET_LIBRARY_VERSION must be defined as 1 in QueueConfig.h to use method.
*/
/**
		* @brief Returns the current version of the Queue Library.
		* @param None
		* @return const BYTE* - The current version of the Queue Library.  This string is 
		(BYTE)NULL terminated.
		* @note USING_QUEUE_GET_LIBRARY_VERSION must be defined as 1 in QueueConfig.h to use method.
		* @sa None
		* @since v1.02
*/
#if (USING_QUEUE_GET_LIBRARY_VERSION == 1)
	const BYTE *QueueGetLibraryVersion(void);
#endif // end of USING_QUEUE_GET_LIBRARY_VERSION

/*
	Macro: UINT32 QueueGetSizeOfNodeInBytes(UINT32 DataSizeInBytes)

	Parameters: 
		UINT32 DataSizeInBytes - The size in bytes of the data being stored in a QUEUE.

	Returns:
		UINT32 - The size in bytes that the QUEUE_NODE takes up with it's accompaning
		data.

	Description: Returns the size of a QUEUE_NODE and it's data in bytes.

	Notes: This method does not take into account how much memory is used to allocate 
	memory through QueueMemAlloc().
*/
#define QueueGetSizeOfNodeInBytes(Size)			(UINT32)(Size + sizeof(QUEUE_NODE))

/*
	Macro: BOOL QueueIsNull(QUEUE *Queue)

	Parameters: 
		QUEUE *Queue - The QUEUE to check if it's NULL or not.

	Returns:
		BOOL - TRUE if the QUEUE is NULL, FALSE otherwise.

	Description: Checks to see if a QUEUE is NULL or not.

	Notes: None
*/
#define QueueIsNull(Queue)						(Queue == (QUEUE*)NULL)

/*
	Macro: BOOL QueueIsEmpty(QUEUE *Queue)

	Parameters: 
		QUEUE *Queue - The QUEUE to check if it's empty or not.

	Returns:
		BOOL - TRUE if the QUEUE is empty, FALSE otherwise.

	Description: Checks to see if the QUEUE is empty.

	Notes: None
*/
#define QueueIsEmpty(Queue)						(Queue->Size == (unsigned int)0)

#endif // end of QUEUE_H
