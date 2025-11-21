#pragma once
#ifndef _IPC_TEST_IPC_INTERFACE_H_
#define _IPC_TEST_IPC_INTERFACE_H_


#include <stdint.h>
#include <semaphore.h>

#include "shm_api_struct.h"


typedef int (*PFN_shmCreate)(const char *const pMainName, const char *const pInfoName, const off_t desiredByteSize, SharedMemoryAttributes *const pAttributes);
typedef int (*PFN_shmOpenExist)(const char *const pMainName, const char *const pInfoName, const off_t desiredByteSize, SharedMemoryAttributes *const pAttributes);

typedef int (*PFN_shmRewrite)(SharedMemoryAttributes *const pAttributes, const void *const pData, const size_t dataByteSize, const size_t indentBytes);
typedef int (*PFN_shmWrite)(SharedMemoryAttributes *const pAttributes, const void *const pData, const size_t dataByteSize, const size_t indentBytes);
typedef int (*PFN_shmClear)(SharedMemoryAttributes *const pAttributes);

typedef int (*PFN_shmGetData)(SharedMemoryAttributes *const pAttributes, void *const pDest, const size_t destByteSize, const size_t indentBytes);

typedef int (*PFN_shmClose)(SharedMemoryAttributes *const pAttributes);
typedef int (*PFN_shmDestroy)(SharedMemoryAttributes *const pAttributes);


static PFN_shmCreate shmCreate;
static PFN_shmOpenExist shmOpenExist;

static PFN_shmRewrite shmRewrite;
static PFN_shmWrite shmWrite;
static PFN_shmClear shmClear;

static PFN_shmGetData shmGetData;

static PFN_shmClose shmClose;
static PFN_shmDestroy shmDestroy;





typedef int (*PFN_ipcShareFd)(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, const int fd);
typedef int (*PFN_ipcGetFd)(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, int *const pFd);


static PFN_ipcShareFd ipcShareFd;
static PFN_ipcGetFd ipcGetFd;



#endif
