#include <shm_api.h>


int ipc_get_fd(SharedMemoryAttributes *const pAttributes, const char *const pMainName, const char *const pInfoName, int *const fd)
{
	shm_open_exist(pMainName, pInfoName, 0, pAttributes);

	pid_t target_process_pid = 0;
	shm_get_data(pAttributes, &target_process_pid, sizeof(target_process_pid), 0);

	int target_process_fd_value = 0;
	shm_get_data(pAttributes, &target_process_fd_value, sizeof(target_process_fd_value), sizeof(target_process_pid));

	printf("pid: %d, fd: %d\n", target_process_pid, target_process_fd_value);


	int pidfd = syscall(SYS_pidfd_open, target_process_pid, 0);

	*fd = syscall(SYS_pidfd_getfd, pidfd, target_process_fd_value, 0);

	fprintf(stderr, "errno: %s\n", strerror(errno));


	return 0;
}
