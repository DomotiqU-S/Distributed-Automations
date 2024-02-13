#include <iostream>
#include <chrono>

//#include "components/DistributedAutomation/DistributedServer.hpp"
#include "components/DistributedAutomation/DistributedDevice.hpp"
//#include "components/DistributedAutomation/Automation/Trigger/TriggerTime.hpp"
#include <thread>


int main(){
    std::thread(&DistributedDevice::Run, &DistributedDevice::Instance()).detach();
    this_thread::sleep_for(chrono::seconds(1));
    DistributedDevice::Instance().TriggerIO("brightness", "50");
    this_thread::sleep_for(chrono::seconds(1));
    DistributedDevice::Instance().TriggerIO("brightness", "25");
    this_thread::sleep_for(chrono::seconds(1));
    DistributedDevice::Instance().TriggerIO("brightness", "50");
    this_thread::sleep_for(chrono::seconds(1));
    DistributedDevice::Instance().Stop();
    this_thread::sleep_for(chrono::seconds(1));

    return 0;
}