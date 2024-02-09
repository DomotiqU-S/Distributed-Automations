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
    bool running;
    mutex cv_m;
    condition_variable cv;

    DistributedDevice();
    ~DistributedDevice();

    void CreateAutomationsThreads();

public:
    static DistributedDevice& Instance(){
        static DistributedDevice instance;
        return instance;
    };

    //Setter
    bool AddAutomation(Automation *automation);
    void RemoveAutomation(string alias);

    //Getter
    vector<Automation *> GetAutomations();

    void UpdateAutomations();

    void TriggerIO(string attribute, string value);

    void Run();
    void Stop();
};


#endif //CPP_DISTRIBUTEDDEVICE_HPP
