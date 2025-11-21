#include <shm_api.h>


int shmRewrite(SharedMemoryAttributes *const pAttributes, const void *const pData, const size_t dataByteSize, const size_t indentBytes)
{
	errno = 0;
	sem_wait(pAttributes->pSemaphore);

	bool resized = false;

	if ((off_t)(dataByteSize + indentBytes) > pAttributes->shmMain.byteSize)
	{
		resized = true;
		off_t oldByteSize = 0;

		oldByteSize = pAttributes->shmMain.byteSize;
		pAttributes->shmMain.byteSize = dataByteSize + indentBytes;

		memcpy(pAttributes->shmInfo.pMappedAddr, &pAttributes->shmMain.byteSize, pAttributes->shmInfo.byteSize);

		ftruncate(pAttributes->shmMain.fd, pAttributes->shmMain.byteSize);
		pAttributes->shmMain.pMappedAddr = mremap(pAttributes->shmMain.pMappedAddr, oldByteSize, pAttributes->shmMain.byteSize, 0, nullptr);
	}

	memcpy(pAttributes->shmMain.pMappedAddr + indentBytes, pData, dataByteSize);

	if (resized == true)
	{
		pAttributes->writedBytes = pAttributes->shmMain.byteSize;
	}
	else
	{
		pAttributes->writedBytes += dataByteSize + indentBytes;
	}


	sem_post(pAttributes->pSemaphore);

	return 0;
}
