#pragma once
#ifndef _IPC_TEST_SHM_API_STRUCT_H_
#define _IPC_TEST_SHM_API_STRUCT_H_


typedef struct SharedMemoryData {
	const char*	pName;
	void*		pMappedAddr;
	off_t		byteSize;
	int		fd;
	uint8_t		nameLen;
} SharedMemoryData;

typedef struct SharedMemoryAttributes {
	SharedMemoryData	shmMain;
	SharedMemoryData	shmInfo;
	sem_t*			pSemaphore;
	size_t			writedBytes;
} SharedMemoryAttributes;


#endif
