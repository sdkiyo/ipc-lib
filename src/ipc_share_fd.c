#include <shm_api.h>


int ipc_share_fd(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, const int fd)
{
	shm_create(pMainName, pInfoName, sizeof(pid_t) + sizeof(int), pAttributes);

	pid_t pid = getpid();

	shm_rewrite(pAttributes, &pid, sizeof(pid), 0);
	printf("pid (%d) writed\n", pid);

	shm_rewrite(pAttributes, &fd, sizeof(fd), sizeof(pid));
	printf("fd (%d) writed\n", fd);

	return 0;
}
