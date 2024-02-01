cmake_minimum_required(VERSION 3.27)
project(distributed-automations)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp main.cpp
        components/DistributedAutomation/Automation/Action/Action.cpp
        components/DistributedAutomation/Automation/Action/ActionCallService.cpp
        components/DistributedAutomation/Automation/Action/ActionDelay.cpp
        components/DistributedAutomation/Automation/Trigger/Trigger.cpp
        components/DistributedAutomation/Automation/Trigger/TriggerNumericState.cpp
        components/DistributedAutomation/Automation/Trigger/TriggerState.cpp
        components/DistributedAutomation/Automation/Trigger/TriggerTime.cpp
        components/DistributedAutomation/Automation/Trigger/TriggerTimePattern.cpp
        components/DistributedAutomation/Automation/Condition/Condition.cpp
        components/DistributedAutomation/Automation/Condition/ConditionLogical.cpp
        components/DistributedAutomation/Automation/Condition/ConditionNumericState.cpp
        components/DistributedAutomation/Automation/Condition/ConditionState.cpp
        components/DistributedAutomation/Automation/Condition/ConditionTime.cpp
        components/DistributedAutomation/Automation/Condition/ConditionTrigger.cpp
        components/DistributedAutomation/Automation/Automation.cpp
        components/DistributedAutomation/DistributedDevice.cpp
        components/DistributedAutomation/DistributedDevice.hpp
        components/DistributedAutomation/DistributedServer.cpp
        components/DistributedAutomation/DistributedServer.hpp
        components/DistributedAutomation/DistributedMatterAPI.cpp
        components/DistributedAutomation/DistributedMatterAPI.hpp
)