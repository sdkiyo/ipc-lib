#pragma once
#ifndef _IPC_TEST_IPC_INTERFACE_H_
#define _IPC_TEST_IPC_INTERFACE_H_


#include <stdint.h>
#include <semaphore.h>

#include "shm_api_struct.h"


typedef int (*PFN_shm_create)(const char *const pMainName, const char *const pInfoName, const off_t desired_byte_size, SharedMemoryAttributes *const pAttributes);
typedef int (*PFN_shm_open_exist)(const char *const pMainName, const char *const pInfoName, const off_t desired_byte_size, SharedMemoryAttributes *const pAttributes);

typedef int (*PFN_shm_rewrite)(SharedMemoryAttributes *const pAttributes, const void *const data, const size_t data_byte_size, const size_t indent_bytes);
typedef int (*PFN_shm_write)(SharedMemoryAttributes *const pAttributes, const void *const data, const size_t data_byte_size, const size_t indent_bytes);
typedef int (*PFN_shm_clear)(SharedMemoryAttributes *const pAttributes);

typedef int (*PFN_shm_get_data)(SharedMemoryAttributes *const pAttributes, void *const dest, const size_t dest_byte_size, const size_t indent_bytes);

typedef int (*PFN_shm_close)(SharedMemoryAttributes *const pAttributes);
typedef int (*PFN_shm_destroy)(SharedMemoryAttributes *const pAttributes);


static PFN_shm_create shm_create;
static PFN_shm_open_exist shm_open_exist;

static PFN_shm_rewrite shm_rewrite;
static PFN_shm_write shm_write;
static PFN_shm_clear shm_clear;

static PFN_shm_get_data shm_get_data;

static PFN_shm_close shm_close;
static PFN_shm_destroy shm_destroy;





typedef int (*PFN_ipc_share_fd)(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, const int fd);
typedef int (*PFN_ipc_get_fd)(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, int *const fd);


static PFN_ipc_share_fd ipc_share_fd;
static PFN_ipc_get_fd ipc_get_fd;



#endif
