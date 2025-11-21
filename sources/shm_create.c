#include <shm_api.h>


int shmCreate(const char *const pMainName, const char *const pInfoName, const off_t desiredByteSize, SharedMemoryAttributes *const pAttributes)
{
	errno = 0;
	pAttributes->shmMain.pName = pMainName;
	pAttributes->shmInfo.pName = pInfoName;

	pAttributes->shmMain.nameLen = strlen(pMainName);
	pAttributes->shmInfo.nameLen = strlen(pInfoName);

	pAttributes->shmInfo.byteSize = sizeof(off_t);
	pAttributes->shmMain.byteSize = desiredByteSize;

	pAttributes->pSemaphore = sem_open(pMainName, O_CREAT|O_EXCL, 0777, 1);

	if (pAttributes->pSemaphore == SEM_FAILED)
	{
		if (errno = EEXIST)
		{
			printf("\033[31m" "semaphore with the same name already exists. try changing the name for shared memory, name: '%s'. or use shm_open_exist() instead of shm_create()" "\033[0m" "\n", pMainName);
		}
		else
		{
			printf("\033[31m" "semaphore failed. semaphore name: '%s', errno: %s" "\033[0m" "\n", pMainName, strerror(errno));
		}

		return -1;
	}

	sem_wait(pAttributes->pSemaphore);

	pAttributes->shmInfo.fd = shm_open(pAttributes->shmInfo.pName, O_CREAT|O_RDWR|O_EXCL, 0777);

	if (pAttributes->shmInfo.fd == -1)
	{
		if (errno = EEXIST)
		{
			printf("\033[31m" "shared memory (info) with same name already exists. shared memory name: '%s'. or use shm_open_exist() instead of shm_create()" "\033[0m" "\n", pAttributes->shmInfo.pName);
		}
		else
		{
			printf("\033[31m" "shared memory (info) failed. shared memory name: '%s', errno: %s" "\033[0m" "\n", pAttributes->shmInfo.pName, strerror(errno));
		}

		return -1;
	}

	pAttributes->shmInfo.pMappedAddr = mmap(nullptr, pAttributes->shmInfo.byteSize, PROT_WRITE|PROT_READ, MAP_SHARED, pAttributes->shmInfo.fd, 0);

	if (pAttributes->shmInfo.pMappedAddr == MAP_FAILED)
	{
		printf("\033[31m" "mmap info error, errno: %s" "\033[0m" "\n", strerror(errno));
		return -1;
	}

	ftruncate(pAttributes->shmInfo.fd, pAttributes->shmInfo.byteSize);

	memcpy(pAttributes->shmInfo.pMappedAddr, &desiredByteSize, pAttributes->shmInfo.byteSize);


	pAttributes->shmMain.fd = shm_open(pAttributes->shmMain.pName, O_CREAT|O_RDWR|O_EXCL, 0777);

	if (pAttributes->shmMain.fd == -1)
	{
		if (errno = EEXIST)
		{
			printf("\033[31m" "shared memory (main) with same name already exists. shared memory name: '%s'. or use shm_open_exist() instead of shm_create()" "\033[0m" "\n", pAttributes->shmMain.pName);
		}
		else
		{
			printf("\033[31m" "shared memory (main) failed. shared memory name: '%s', errno: %s" "\033[0m" "\n", pAttributes->shmMain.pName, strerror(errno));
		}

		return -1;
	}

	pAttributes->shmMain.pMappedAddr = mmap(nullptr, pAttributes->shmMain.byteSize, PROT_WRITE|PROT_READ, MAP_SHARED, pAttributes->shmMain.fd, 0);

	if (pAttributes->shmMain.pMappedAddr == MAP_FAILED)
	{
		printf("\033[31m" "mmap main error, errno: %s" "\033[0m" "\n", strerror(errno));
		return -1;
	}

	ftruncate(pAttributes->shmMain.fd, pAttributes->shmMain.byteSize);


	sem_post(pAttributes->pSemaphore);

	return 0;
}
