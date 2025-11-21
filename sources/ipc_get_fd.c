#include <shm_api.h>


int ipcGetFd(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, int *const pFd)
{
	errno = 0;

	if (shmOpenExist(pMainName, pInfoName, 0, pAttributes) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'shmOpenExist() failed' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	pid_t targetProcessPid = 0;
	if (shmGetData(pAttributes, &targetProcessPid, sizeof(targetProcessPid), 0) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'shmGetData() failed' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	const int pidFd = syscall(SYS_pidfd_open, targetProcessPid, 0);

	if (pidFd == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'pidFd have -1 value after syscall(SYS_pidfd_open, targetProcessPid, 0)' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	int targetProcessFdValue = 0;
	if (shmGetData(pAttributes, &targetProcessFdValue, sizeof(targetProcessFdValue), sizeof(targetProcessPid)) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'shmGetData() failed' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	*pFd = syscall(SYS_pidfd_getfd, pidFd, targetProcessFdValue, 0);

	if (*pFd == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'final pFd have -1 value after syscall(SYS_pidfd_getfd, pidFd, targetProcessFdValue, 0)' errno: %s" RESET_COLOR "\n", __func__, __LINE__, strerror(errno));
		return -1;
	}

	return 0;
}
