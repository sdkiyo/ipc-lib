#include <stdio.h>
#include <dlfcn.h>
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

	SharedMemoryAttributes shmAttributes = {};
	//shm_create("test", "test.info", 24, &shmAttributes);
	shm_open_exist("test", "test.info", 12, &shmAttributes);

	char msg1[] = "test msg";
	char msg2[] = "TEST_MSG_2";

	getchar();
	shm_rewrite(&shmAttributes, msg1, sizeof(msg1), 0);
	printf("rewrited\n");

	getchar();
	shm_write(&shmAttributes, msg2, sizeof(msg2), 2);
	printf("writed\n");

	getchar();
	shm_clear(&shmAttributes);
	printf("clear\n");


	getchar();
	shm_close(&shmAttributes);
	printf("closed\n");
	//shm_destroy(&shmAttributes);


	printf("\033[2mtest1\033[0m\n");
	return 0;
}
