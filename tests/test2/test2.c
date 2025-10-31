#include <stdio.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../include/ipc_interface.h"




int main()
{
	printf("\033[2mtest1\033[0m\n");


	void* ipc_lib = dlopen("./lib_ipc_test.so", RTLD_LAZY);

	shm_create = dlsym(ipc_lib, "shm_create");
	shm_open_exist = dlsym(ipc_lib, "shm_open_exist");

	shm_rewrite = dlsym(ipc_lib, "shm_rewrite");
	shm_write = dlsym(ipc_lib, "shm_write");
	shm_clear = dlsym(ipc_lib, "shm_clear");

	shm_close = dlsym(ipc_lib, "shm_close");
	shm_destroy = dlsym(ipc_lib, "shm_destroy");

	ipc_share_fd = dlsym(ipc_lib, "ipc_share_fd");


	SharedMemoryAttributes shmAttributes = {};

	int fd = open("file.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

	ipc_share_fd(&shmAttributes, "test2", "test2.info", fd);


	char ch = ' ';
	while(ch != 'q')
	{
		ch = getchar();
	}

	close(fd);

	shm_destroy(&shmAttributes);
	printf("destroyed\n");

	dlclose(ipc_lib);


	printf("\033[2mtest1\033[0m\n");
	return 0;
}
