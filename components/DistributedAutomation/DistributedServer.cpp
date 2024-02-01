//
// Created by talgarr on 01/02/24.
//
#include "DistributedServer.hpp"


DistributedServer::DistributedServer() {
    this->devices_alias = vector<string>();
    this->automations_by_devices = map<string, vector<Automation>>();

    ReadAutomations();
    this->devices_alias = DistributedMatterAPI::GetDevices();
    FetchAutomationsFromAllDevices();
}

DistributedServer::~DistributedServer() {
    this->devices_alias.clear();
    for (auto &automations: this->automations_by_devices) {
        automations.second.clear();
    }
    this->automations_by_devices.clear();
}

bool DistributedServer::AddDevice(const string &alias) {
    this->devices_alias.push_back(alias);
    this->automations_by_devices[alias] = vector<Automation>();
    return true;
}

bool DistributedServer::AddAutomationToDevice(const string &device_alias, Automation automation) {
    for (auto &automat: this->automations_by_devices[device_alias]) {
        if (automat.GetAlias() == automation.GetAlias()) {
            return false;
        }
    }
    if (DistributedMatterAPI::AddAutomationToDevice(device_alias, automation)) {
        this->automations_by_devices[device_alias].push_back(automation);
        return true;
    } else {
        return false;
    }
}

void DistributedServer::RemoveAutomationFromDevice(const string& device_alias, string automation_alias) {
    this->automations_by_devices[device_alias].erase(std::remove_if(this->automations_by_devices[device_alias].begin(),
                                                                    this->automations_by_devices[device_alias].end(),
                                                                    [&automation_alias](Automation &automat) {
                                                                        return automat.GetAlias() == automation_alias;
                                                                    }),
                                                     this->automations_by_devices[device_alias].end());
}

void DistributedServer::FetchAutomationsFromDevice(const string& alias) {
    for (auto &device: this->devices_alias) {
        if (device == alias) {
            {
                this->automations_by_devices[alias] = DistributedMatterAPI::GetAutomations(alias);
                return;
            }
        }
    }
}

void DistributedServer::FetchAutomationsFromAllDevices() {
    for (auto &device: this->devices_alias) {
        FetchAutomationsFromDevice(device);
    }
}

void DistributedServer::Run() {

}

void DistributedServer::ReadAutomations() {

}

void DistributedServer::WriteAutomations() {

}

