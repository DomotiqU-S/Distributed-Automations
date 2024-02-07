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
    for (auto &automation: this->automations) {
        automation->Stop();
        delete automation;
    }
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
    this->automations = DistributedMatterAPI::GetAutomations("");
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
        this->automations_threads.push_back(std::move(t));
    }

}

void DistributedDevice::Stop() {
    unique_lock<mutex> lock(this->cv_m);
    this->running = false;
    for (auto &t: this->automations) {
        t->Stop();
    }
    this->cv.notify_all();
//    this->automations.clear();
//    this->automations_threads.clear();
}

