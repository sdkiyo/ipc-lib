#pragma once
#ifndef _IPC_TEST_SHM_API_H_
#define _IPC_TEST_SHM_API_H_


#include "includes.h"
#include "shm_api_struct.h"


int shmCreate(const char *const pMainName, const char *const pInfoName, const off_t desiredByteSize, SharedMemoryAttributes *const pAttributes);
int shmOpenExist(const char *const pMainName, const char *const pInfoName, const off_t desiredByteSize, SharedMemoryAttributes *const pAttributes);

int shmRewrite(SharedMemoryAttributes *const pAttributes, const void *const pData, const size_t dataByteSize, const size_t indentBytes);
int shmGetData(SharedMemoryAttributes *const pAttributes, void *const pDest, const size_t destByteSize, const size_t indentBytes);



#endif
