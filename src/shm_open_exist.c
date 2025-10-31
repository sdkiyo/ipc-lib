#include <shm_api.h>


int shm_open_exist(const char *const pMainName, const char *const pInfoName, const off_t desired_byte_size, SharedMemoryAttributes *const pAttributes)
{
	errno = 0;
	pAttributes->shmMain.pName = pMainName;
	pAttributes->shmInfo.pName = pInfoName;

	pAttributes->shmMain.name_len = strlen(pMainName);
	pAttributes->shmInfo.name_len = strlen(pInfoName);

	pAttributes->shmInfo.byte_size = sizeof(off_t);
	pAttributes->shmMain.byte_size = desired_byte_size;

	pAttributes->pSemaphore = sem_open(pMainName, O_EXCL, 0777, 1);

	if (pAttributes->pSemaphore == SEM_FAILED)
	{
		if (errno = EEXIST)
		{
			printf("\033[31m" "semaphore with the same name not exists. try changing the name for shared memory, name: '%s'. or use shm_create() instead of shm_open_exist()" "\033[0m" "\n", pMainName);
		}
		else
		{
			printf("\033[31m" "semaphore failed. semaphore name: '%s', errno: %s" "\033[0m" "\n", pMainName, strerror(errno));
		}

		return -1;
	}

	sem_wait(pAttributes->pSemaphore);

	pAttributes->shmInfo.fd = shm_open(pAttributes->shmInfo.pName, O_EXCL|O_RDWR, 0777);

	if (pAttributes->shmInfo.fd == -1)
	{
		if (errno = EEXIST)
		{
			printf("\033[31m" "shared memory (info) with same name not exists. shared memory name: '%s. or use shm_create() instead of shm_open_exist()'" "\033[0m" "\n", pAttributes->shmInfo.pName);
		}
		else
		{
			printf("\033[31m" "shared memory (info) failed. shared memory name: '%s', errno: %s" "\033[0m" "\n", pAttributes->shmInfo.pName, strerror(errno));
		}

		return -1;
	}

	pAttributes->shmInfo.pMappedAddr = mmap(nullptr, pAttributes->shmInfo.byte_size, PROT_WRITE|PROT_READ, MAP_SHARED, pAttributes->shmInfo.fd, 0);

	if (pAttributes->shmInfo.pMappedAddr == MAP_FAILED)
	{
		printf("\033[31m" "mmap (info) error, errno: %s" "\033[0m" "\n", strerror(errno));
		return -1;
	}

	ftruncate(pAttributes->shmInfo.fd, pAttributes->shmInfo.byte_size);

	off_t old_mem_size = 0;

	memcpy(&old_mem_size, pAttributes->shmInfo.pMappedAddr, pAttributes->shmInfo.byte_size);

	if (old_mem_size == 0 || old_mem_size < desired_byte_size)
	{
		memcpy(pAttributes->shmInfo.pMappedAddr, &pAttributes->shmMain.byte_size, pAttributes->shmInfo.byte_size);
	}
	else
	{
		pAttributes->shmMain.byte_size = old_mem_size;
	}


	pAttributes->shmMain.fd = shm_open(pAttributes->shmMain.pName, O_EXCL|O_RDWR, 0777);

	if (pAttributes->shmMain.fd == -1)
	{
		if (errno = EEXIST)
		{
			printf("\033[31m" "shared memory (main) with same name not exists. shared memory name: '%s'. or use shm_create() instead of shm_open_exist()" "\033[0m" "\n", pAttributes->shmMain.pName);
		}
		else
		{
			printf("\033[31m" "shared memory (main) failed. shared memory name: '%s', errno: %s" "\033[0m" "\n", pAttributes->shmMain.pName, strerror(errno));
		}

		return -1;
	}
	pAttributes->shmMain.pMappedAddr = mmap(nullptr, pAttributes->shmMain.byte_size, PROT_WRITE|PROT_READ, MAP_SHARED, pAttributes->shmMain.fd, 0);

	if (pAttributes->shmMain.pMappedAddr == MAP_FAILED)
	{
		printf("\033[31m" "mmap (main) error, errno: %s" "\033[0m" "\n", strerror(errno));
		return -1;
	}

	ftruncate(pAttributes->shmMain.fd, pAttributes->shmMain.byte_size);


	sem_post(pAttributes->pSemaphore);

	return 0;
}
