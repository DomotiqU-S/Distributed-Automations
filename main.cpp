#include <iostream>

#include "components/DistributedAutomation/DistributedServer.hpp"
#include "components/DistributedAutomation/DistributedDevice.hpp"
#include "components/DistributedAutomation/Automation/Trigger/TriggerTime.hpp"


int main() {
//    xTaskCreate(DistributedServer::Run, "server_main", 20480, xTaskGetCurrentTaskHandle(), 5, NULL);
//    DistributedServer::Run();
    auto device = DistributedDevice();
    auto t = thread(&DistributedDevice::Run, &device);

    this_thread::sleep_for(chrono::seconds(21));
    device.Stop();

    cout << "Hello, World!" << endl;
    t.join();



    return 0;
}
