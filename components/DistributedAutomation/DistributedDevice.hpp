//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_DISTRIBUTEDDEVICE_HPP
#define CPP_DISTRIBUTEDDEVICE_HPP


#include <map>
#include "Automation/Automation.hpp"

class DistributedDevice {
private:
    vector<Automation> automations;

public:
    DistributedDevice();
    ~DistributedDevice();

    //Setter
    bool AddAutomation(Automation *automation);
    void RemoveAutomation(string alias);

    //Getter
    vector<Automation> GetAutomations();

    void UpdateAutomations();

    void Run();
};


#endif //CPP_DISTRIBUTEDDEVICE_HPP
