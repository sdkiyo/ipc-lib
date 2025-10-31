#include <shm_api.h>


int shm_clear(SharedMemoryAttributes *const pAttributes)
{
	for (off_t i = 0; i < pAttributes->shmMain.byte_size; i++)
	{
		if (shm_rewrite(pAttributes, "\0", 1, 0+i) == -1)
		{
			printf("failed\n");
		}
	}

	return 0;
}
