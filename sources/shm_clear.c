#include <shm_api.h>


int shmClear(SharedMemoryAttributes *const pAttributes)
{
	for (off_t i = 0; i < pAttributes->shmMain.byteSize; i++)
	{
		if (shmRewrite(pAttributes, "\0", 1, 0+i) == -1)
		{
			printf("failed\n");
		}
	}

	return 0;
}
