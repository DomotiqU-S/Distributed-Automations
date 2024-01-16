cmake_minimum_required(VERSION 3.27)
project(distributed_server C)

set(CMAKE_C_STANDARD 23)

add_executable(distributed_server main.c
        automation/Automation.c
        library/cJSON.c
        automation/DistributedServer.c
        automation/MatterAPI.c
        automation/DistributedDevice.c
)
