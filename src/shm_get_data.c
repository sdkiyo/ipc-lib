#include <shm_api.h>


int shm_get_data(SharedMemoryAttributes *const pAttributes, void *const dest, const size_t dest_byte_size, const size_t indent_bytes)
{
	sem_wait(pAttributes->pSemaphore);

	if (indent_bytes > (pAttributes->shmMain.byte_size - 1))
	{
		fprintf(stderr, "\033[31mindent > memory size\033[0m\n");
		return -1;
	}

	memcpy(dest, pAttributes->shmMain.pMappedAddr + indent_bytes, dest_byte_size);

	sem_post(pAttributes->pSemaphore);

	return 0;
}
