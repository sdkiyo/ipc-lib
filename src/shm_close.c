#include <shm_api.h>


int shm_close(SharedMemoryAttributes *const pAttributes)
{
	errno = 0;
	sem_wait(pAttributes->pSemaphore);

	if (munmap(pAttributes->shmMain.pMappedAddr, pAttributes->shmMain.byte_size) == -1)
	{
		printf("\033[31mmunmap() (main) failed\033[0m\n");
		return -1;
	}

	if (munmap(pAttributes->shmInfo.pMappedAddr, pAttributes->shmInfo.byte_size) == -1)
	{
		printf("\033[31mmunmap() (info) failed\033[0m\n");
		return -1;
	}

	sem_post(pAttributes->pSemaphore);
	sem_close(pAttributes->pSemaphore);

	return 0;
}
