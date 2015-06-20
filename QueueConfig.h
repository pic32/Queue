/*
	Date: June 24, 2011
	File Name: QueueConfig.h
	Version: 1.03
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file configures the options built into the Queue Library.
	The below set of defines allows the user to enable certain methods
	located inside the Queue library.

	It also allows the user to define how the Queue library will
	allocate and deallocate memory for new nodes.

	All methods are thread safe(re-entrant), with the potential exception of
	QueueCreate, QueueAdd, QueueRemove, and QueueClear.  The reason
	for this is that it all depends on how the user defines the 
	way the Queue library will allocate, deallocate memory.
*/

#ifndef QUEUE_CONFIG_H
	#define QUEUE_CONFIG_H

/**
	*Set USING_QUEUE_PEEK_METHOD to 1 to enable the
	QueuePeek method.
*/
#define USING_QUEUE_PEEK_METHOD							1

/**
	*Set USING_QUEUE_CLEAR_METHOD to 1 to enable the
	QueueClear method.
*/ 
#define USING_QUEUE_CLEAR_METHOD						1

/**
	*Set USING_QUEUE_GET_SIZE_METHOD to 1 to enable the
	QueueGetSize method.
*/
#define USING_QUEUE_GET_SIZE_METHOD						1

/**
	*Set USING_QUEUE_GET_SIZE_IN_BYTES_METHOD to 1 to enable the
	QueueGetSizeInBytes method.
*/
#define USING_QUEUE_GET_SIZE_IN_BYTES_METHOD			1

/**
	*Set USING_QUEUE_GET_LIBRARY_VERSION to 1 to enable getting
	the current version of the QUEUE Library.
*/
#define USING_QUEUE_GET_LIBRARY_VERSION					1

/**
	*Set QUEUE_SAFE_MODE to 1 to enable the portions of code
	inside the QUEUE Library that check to make sure all passed
	in parameters are of a valid nature.
*/
#define QUEUE_SAFE_MODE									1

/**
	*The below defines what method the Queue library will use to 
	allocate memory and deallocated.  This allows the Queue 
	library to be integrated into an OS.
*/
#define QueueMemAlloc(Mem)								malloc(Mem)

/**
	*The method for freeing up memory.
*/
#define QueueMemDealloc(Mem)							free(Mem)

/**
	*Define USE_MALLOC as 1 to enable the stdlib.h file included
	with Queue.c.
*/
#define USE_MALLOC										1

/*
	*Define the below as 1 if each QUEUE is to store a custom
	method for freeing a QUEUE_NODE.
*/
#define USING_QUEUE_DEPENDENT_FREE_METHOD				1

/**
	*If the user isn't using malloc then include the file that will
	be needed for accessing whatever method MemAlloc() and MemDealloc()
	implement, below.
*/
//#include "Your memory file here.h"

#endif // end of QUEUE_CONFIG_H
