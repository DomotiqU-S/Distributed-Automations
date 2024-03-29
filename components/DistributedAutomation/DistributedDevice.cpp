//
// Created by talgarr on 01/02/24.
//

#include <thread>
#include "DistributedDevice.hpp"
#include "DistributedMatterAPI.hpp"

DistributedDevice::DistributedDevice(){
    this->running = true;
    this->automations = vector<Automation*>();
}

DistributedDevice::~DistributedDevice(){
    this->running = false;
    for (auto &automation: this->automations) {
        automation->Stop();
        delete automation;
    }
    this->automations.clear();
}

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

void DistributedDevice::Run() {
    if (this->automations.empty()) {
        return;
    }
    this->CreateAutomationsThreads();
    while (this->running) {
        unique_lock<mutex> lock(this->cv_m);
        for (auto &automation: this->automations) {
            if(automation->HasTriggered()){
                if (automation->Verify())
                    automation->Do();
            }
        }
        this->cv.wait(lock);
    }
}

vector<Automation *> DistributedDevice::GetAutomations() {
    return this->automations;
}

void DistributedDevice::CreateAutomationsThreads() {
    for (auto automation: this->automations) {
        thread t(&Automation::Run, automation, &this->cv, &this->cv_m);
        t.detach();
    }

}

void DistributedDevice::Stop() {
    unique_lock<mutex> lock(this->cv_m);
    this->running = false;
    for (auto &t: this->automations) {
        t->Stop();
    }
    this->cv.notify_all();
    this->automations.clear();
}

void DistributedDevice::TriggerIO(const string& attribute, const string& value) {
    if (this->states[attribute].value == value) {
        return;
    }
    this->states[attribute] = State(time(nullptr), value);
    for (auto &automation: this->automations) {
        automation->IO(attribute, value);
    }
}

State DistributedDevice::GetAttribute(const string& attribute) {
    if (this->states.find(attribute) == this->states.end()) {
        return {};
    }
    return this->states[attribute];
}

//DistributedDevice *DistributedDevice::GetInstance() {
//    lock_guard<mutex> lock(mutex_singleton);
//    if (instance == nullptr)
//    {
//        instance = new DistributedDevice();
//    }
//    return instance;
//}

