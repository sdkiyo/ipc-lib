#pragma once
#ifndef _IPC_TEST_SHM_API_H_
#define _IPC_TEST_SHM_API_H_


#include "includes.h"
#include "shm_api_struct.h"


int shm_create(const char *const pMainName, const char *const pInfoName, const off_t desired_byte_size, SharedMemoryAttributes *const pAttributes);
int shm_open_exist(const char *const pMainName, const char *const pInfoName, const off_t desired_byte_size, SharedMemoryAttributes *const pAttributes);

int shm_rewrite(SharedMemoryAttributes *const pAttributes, const void *const data, const size_t data_byte_size, const size_t indent_bytes);
int shm_get_data(SharedMemoryAttributes *const pAttributes, void *const dest, const size_t dest_byte_size, const size_t indent_bytes);



#endif
