cmake_minimum_required(VERSION 3.27)
project(distributed_server C)

set(CMAKE_C_STANDARD 23)

add_executable(distributed_server main.c
        components/Test/Test_DistributedAutomation/Test_Automation/Test_Action.c
        components/Test/Test_DistributedAutomation/Test_Automation/Test_Automation.c
        components/Test/Test_DistributedAutomation/Test_Automation/Test_Trigger.c
        components/Library/cJSON.c
        components/DistributedAutomation/DistributedServer.c
        components/DistributedAutomation/DistributedMatterAPI.c
        components/DistributedAutomation/Automation/Condition.c
        components/DistributedAutomation/DistributedDevice.c
        components/DistributedAutomation/Automation/Action.c
        components/DistributedAutomation/Automation/Automation.c
        components/DistributedAutomation/Automation/Trigger.c
        components/Utils/VectorUtils.c
        components/Test/Test_DistributedAutomation/Test_Automation/Test_Condition.c
        components/Test/Test_DistributedAutomation/Test_Automation/Test_Condition.h

)
