cmake_minimum_required(VERSION 4.1.2)

project(test1 LANGUAGES C)
set(CMAKE_C_STANDARD 23)

set(P ../../src/)
add_library(ipc_test SHARED
	${P}shm_create.c
	${P}shm_open_exist.c
	${P}shm_get_data.c
	${P}shm_close.c
	${P}shm_destroy.c
	${P}shm_rewrite.c
	${P}shm_write.c
	${P}shm_clear.c
)
target_include_directories(ipc_test PUBLIC ../../include)
set_target_properties(ipc_test PROPERTIES
	PREFIX "lib_"
	OUTPUT_NAME "ipc_test"
	SUFFIX ".so")


add_executable(${PROJECT_NAME} main.c)
