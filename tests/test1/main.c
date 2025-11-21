#include <stdio.h>
#include <dlfcn.h>
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

	ipcGetFd = dlsym(ipc_lib, "ipcGetFd");
	ipcShareFd = dlsym(ipc_lib, "ipcShareFd");
	shmGetData = dlsym(ipc_lib, "shmGetData");

	SharedMemoryAttributes shmAttributes = {};
	shmCreate("test", "test.info", 24, &shmAttributes);
	//shmOpenExist("test", "test.info", 12, &shmAttributes);

	char msg1[] = "test msg";
	char msg2[] = "TEST_MSG_2";

	getchar();
	shmRewrite(&shmAttributes, msg1, sizeof(msg1), 0);
	printf("rewrited\n");

	getchar();
	shmWrite(&shmAttributes, msg2, sizeof(msg2), 2);
	printf("writed\n");

	getchar();
	shmClear(&shmAttributes);
	printf("clear\n");


//	getchar();
//	shmClose(&shmAttributes);
//	printf("closed\n");
	getchar();
	shmDestroy(&shmAttributes);
	printf("destroyed\n");


	printf("\033[2mtest1\033[0m\n");
	return 0;
}
