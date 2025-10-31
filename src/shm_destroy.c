#include <shm_api.h>


int shm_destroy(SharedMemoryAttributes *const pAttributes)
{
	errno = 0;
	sem_wait(pAttributes->pSemaphore);

	if (munmap(pAttributes->shmMain.pMappedAddr, pAttributes->shmMain.byte_size) == -1)
	{
		printf("\033[31mmunmap() (main) failed\033[0m\n");
		return -1;
	}

	if (shm_unlink(pAttributes->shmMain.pName) == -1)
	{
		printf("\033[31mshm_unlink() (main) failed\033[0m\n");
		return -1;
	}

	if (munmap(pAttributes->shmInfo.pMappedAddr, pAttributes->shmInfo.byte_size) == -1)
	{
		printf("\033[31mmunmap() (info) failed\033[0m\n");
		return -1;
	}

	if (shm_unlink(pAttributes->shmInfo.pName) == -1)
	{
		printf("\033[31mshm_unlink() (info) failed\033[0m\n");
		return -1;
	}

	sem_close(pAttributes->pSemaphore);
	sem_unlink(pAttributes->shmMain.pName);

	return 0;
}
