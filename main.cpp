#include <iostream>
#include <chrono>

//#include "components/DistributedAutomation/DistributedServer.hpp"
//#include "components/DistributedAutomation/DistributedDevice.hpp"
//#include "components/DistributedAutomation/Automation/Trigger/TriggerTime.hpp"
#include "components/singleton.h"

constexpr auto tenMill= 10000000;

int main(){

    constexpr auto fourtyMill= 4* tenMill;

    auto begin= std::chrono::system_clock::now();

    for ( size_t i= 0; i <= fourtyMill; ++i){
        MySingleton::getInstance();
    }

    auto end= std::chrono::system_clock::now() - begin;

    std::cout << std::chrono::duration<double>(end).count() << std::endl;

}