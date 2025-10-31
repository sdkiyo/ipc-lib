#include <shm_api.h>


int shm_rewrite(SharedMemoryAttributes *const pAttributes, const void *const data, const size_t data_byte_size, const size_t indent_bytes)
{
	errno = 0;
	sem_wait(pAttributes->pSemaphore);

	bool resized = false;

	if ((data_byte_size + indent_bytes) > pAttributes->shmMain.byte_size)
	{
		resized = true;
		off_t old_byte_size = 0;

		old_byte_size = pAttributes->shmMain.byte_size;
		pAttributes->shmMain.byte_size = data_byte_size + indent_bytes;

		memcpy(pAttributes->shmInfo.pMappedAddr, &pAttributes->shmMain.byte_size, pAttributes->shmInfo.byte_size);

		ftruncate(pAttributes->shmMain.fd, pAttributes->shmMain.byte_size);
		pAttributes->shmMain.pMappedAddr = mremap(pAttributes->shmMain.pMappedAddr, old_byte_size, pAttributes->shmMain.byte_size, 0, nullptr);
	}

	memcpy(pAttributes->shmMain.pMappedAddr + indent_bytes, data, data_byte_size);

	if (resized == true)
	{
		pAttributes->writed_bytes = pAttributes->shmMain.byte_size;
	}
	else
	{
		pAttributes->writed_bytes += data_byte_size + indent_bytes;
	}


	sem_post(pAttributes->pSemaphore);

	return 0;
}
