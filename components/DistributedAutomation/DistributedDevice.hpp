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
    static DistributedDevice *instance;
    static mutex mutex_singleton;

    vector<Automation *> automations;
    bool running;
    static mutex cv_m;
    static condition_variable cv;

    DistributedDevice();
    ~DistributedDevice();

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

    void Run();
    void Stop();

    void CreateAutomationsThreads();
};


#endif //CPP_DISTRIBUTEDDEVICE_HPP
