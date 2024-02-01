//
// Created by talgarr on 01/02/24.
//

#include <thread>
#include "DistributedDevice.hpp"
#include "DistributedMatterAPI.hpp"

DistributedDevice::DistributedDevice(){
    this->running = true;
    this->automations = vector<Automation*>();
    this->automations_threads = vector<thread>();
}

DistributedDevice::~DistributedDevice(){
    this->running = false;
    this->cv.notify_all();
    for (auto &t: this->automations_threads) {
        t.join();
    }
    this->automations.clear();
    this->automations_threads.clear();
};

bool DistributedDevice::AddAutomation(Automation *automation) {
    for (auto &automat : this->automations) {
        if (automat->GetAlias() == automation->GetAlias()) {
            return false;
        }
    }
    this->automations.push_back(automation);
    return true;
}

void DistributedDevice::RemoveAutomation(string alias) {
    for (auto &automat : this->automations) {
        if (automat->GetAlias() == alias) {
            this->automations.erase(std::remove(this->automations.begin(), this->automations.end(), automat), this->automations.end());
            return;
        }
    }
}

void DistributedDevice::UpdateAutomations() {
}

void DistributedDevice::Run() {
    auto device = DistributedDevice();
    device.automations = DistributedMatterAPI::GetAutomations("");
    device.CreateAutomationsThreads();
    while (device.running) {
        unique_lock<mutex> lock(device.cv_m);
        for (auto &automation: device.automations) {
            if(automation->HasTriggered()){
                if (automation->Verify())
                    automation->Do();
            }
        }
        device.cv.wait(lock);
    }
}

vector<Automation *> DistributedDevice::GetAutomations() {
    return this->automations;
}

void DistributedDevice::CreateAutomationsThreads() {
    for (auto automation: this->automations) {
        thread t(&Automation::Run, automation, &this->cv, &this->cv_m);
        this->automations_threads.push_back(std::move(t));
    }

}

