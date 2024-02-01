#include <iostream>

#include "components/DistributedAutomation/DistributedServer.hpp"
#include "components/DistributedAutomation/DistributedDevice.hpp"


int main() {
//    xTaskCreate(DistributedServer::Run, "server_main", 20480, xTaskGetCurrentTaskHandle(), 5, NULL);
//    DistributedServer::Run();
    DistributedDevice::Run();

    return 0;
}
