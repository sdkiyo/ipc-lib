#include <shm_api.h>


int ipcShareFd(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, const int fd)
{
	pid_t pid = getpid();

	if (shmCreate(pMainName, pInfoName, sizeof(pid) + sizeof(fd), pAttributes) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'shmCreate() failed' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	if (shmRewrite(pAttributes, &pid, sizeof(pid), 0) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'shmRewrite() failed' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	if (shmRewrite(pAttributes, &fd, sizeof(fd), sizeof(pid)) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'shmRewrite() failed' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	return 0;
}
