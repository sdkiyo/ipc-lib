#include <stdio.h>
#include <dlfcn.h>
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

	ipc_get_fd = dlsym(ipc_lib, "ipc_get_fd");


	SharedMemoryAttributes shmAttributes = {};

	int fd = 0;

	ipc_get_fd(&shmAttributes, "test2", "test2.info", &fd);

	printf("new fd: %d\n", fd);

	if (write(fd, "AAA", sizeof("AAA")) == -1)
	{
		printf("write error\n");
	}



	getchar();
	shm_close(&shmAttributes);
	printf("closed\n");
	//shm_destroy(&shmAttributes);

	dlclose(ipc_lib);


	printf("\033[2mtest1\033[0m\n");
	return 0;
}
