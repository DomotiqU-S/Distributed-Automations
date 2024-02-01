//
// Created by talgarr on 01/02/24.
//

#include "DistributedDevice.hpp"

DistributedDevice::DistributedDevice() = default;

DistributedDevice::~DistributedDevice() = default;

bool DistributedDevice::AddAutomation(Automation *automation) {
    for (auto &automat : this->automations) {
        if (automat.GetAlias() == automation->GetAlias()) {
            return false;
        }
    }
    this->automations.push_back(*automation);
    return true;
}

void DistributedDevice::RemoveAutomation(string alias) {
    this->automations.erase(std::remove_if(this->automations.begin(), this->automations.end(), [&alias](Automation &automat) {
        return automat.GetAlias() == alias;
    }), this->automations.end());
}

void DistributedDevice::UpdateAutomations() {
}

void DistributedDevice::Run() {

}

vector<Automation> DistributedDevice::GetAutomations() {
    return this->automations;
}

