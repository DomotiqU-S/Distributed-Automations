//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_DISTRIBUTEDDEVICE_HPP
#define CPP_DISTRIBUTEDDEVICE_HPP


#include <map>
#include <thread>
#include <condition_variable>
#include "Automation/Automation.hpp"

class DistributedDevice {
private:
    vector<Automation *> automations;
    vector<thread> automations_threads;
    bool running;
    mutex cv_m;
    condition_variable cv;

public:
    DistributedDevice();
    ~DistributedDevice();

    //Setter
    bool AddAutomation(Automation *automation);
    void RemoveAutomation(string alias);

    //Getter
    vector<Automation *> GetAutomations();

    void UpdateAutomations();

    void Run();
    void Stop();

    void CreateAutomationsThreads();
};


#endif //CPP_DISTRIBUTEDDEVICE_HPP
