#include <shm_api.h>


int shmGetData(SharedMemoryAttributes *const pAttributes, void *const dest, const size_t destByteSize, const size_t indentBytes)
{
	sem_wait(pAttributes->pSemaphore);

	if ((off_t)indentBytes > (pAttributes->shmMain.byteSize - 1))
	{
		fprintf(stderr, "\033[31mindent > memory size\033[0m\n");
		return -1;
	}

	memcpy(dest, pAttributes->shmMain.pMappedAddr + indentBytes, destByteSize);

	sem_post(pAttributes->pSemaphore);

	return 0;
}
