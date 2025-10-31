#pragma once
#ifndef _IPC_TEST_SHM_API_STRUCT_H_
#define _IPC_TEST_SHM_API_STRUCT_H_


typedef struct SharedMemoryData {
	const char*	pName;
	void*		pMappedAddr;
	off_t		byte_size;
	int		fd;
	uint8_t		name_len;
} SharedMemoryData;

typedef struct SharedMemoryAttributes {
	SharedMemoryData	shmMain;
	SharedMemoryData	shmInfo;
	sem_t*			pSemaphore;
	size_t			writed_bytes;
} SharedMemoryAttributes;


#endif
