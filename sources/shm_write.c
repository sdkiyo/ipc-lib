#include <shm_api.h>


int shmWrite(SharedMemoryAttributes *const pAttributes, const void *const pData, const size_t dataByteSize, const size_t indentBytes)
{
	shmRewrite(pAttributes, pData, dataByteSize, indentBytes + pAttributes->writedBytes);

	return 0;
}
