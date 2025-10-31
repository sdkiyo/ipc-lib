#include <shm_api.h>


int shm_write(SharedMemoryAttributes *const pAttributes, const void *const data, const size_t data_byte_size, const size_t indent_bytes)
{
	shm_rewrite(pAttributes, data, data_byte_size, indent_bytes + pAttributes->writed_bytes);

	return 0;
}
