//
// Created by talgarr on 01/02/24.
//

#include "ActionCallService.hpp"

#include <utility>

ActionCallService::ActionCallService(string alias, string service, string service_data)
        : Action(std::move(alias)) {
    this->service  = std::move(service);
    this->service_data = std::move(service_data);
}

ActionCallService::~ActionCallService() = default;

void ActionCallService::Do() {
    std::cout << "AcitonCallService Do" << std::endl;
}


