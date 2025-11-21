#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include "../../includes/ipc_interface.h"




int main()
{
	printf("\033[2mtest1\033[0m\n");


	void* ipc_lib = dlopen("./lib_ipc_test.so", RTLD_LAZY);

	shmCreate = dlsym(ipc_lib, "shmCreate");
	shmOpenExist = dlsym(ipc_lib, "shmOpenExist");

	shmRewrite = dlsym(ipc_lib, "shmRewrite");
	shmWrite = dlsym(ipc_lib, "shmWrite");
	shmClear = dlsym(ipc_lib, "shmClear");

	shmClose = dlsym(ipc_lib, "shmClose");
	shmDestroy = dlsym(ipc_lib, "shmDestroy");

	ipcShareFd = dlsym(ipc_lib, "ipcShareFd");
	ipcGetFd = dlsym(ipc_lib, "ipcGetFd");
	shmGetData = dlsym(ipc_lib, "shmGetData");


	SharedMemoryAttributes shmAttributes = {};

	int fd = 0;

	ipcGetFd(&shmAttributes, "test2", "test2.info", &fd);

	printf("new fd: %d\n", fd);

	if (write(fd, "AAA", sizeof("AAA")) == -1)
	{
		printf("write error\n");
	}



	getchar();
	shmClose(&shmAttributes);
	printf("closed\n");
	//shmDestroy(&shmAttributes);

	dlclose(ipc_lib);


	printf("\033[2mtest1\033[0m\n");
	return 0;
}
