//
// Created by talgarr on 01/02/24.
//

#include "ActionCallService.hpp"

#include <utility>

ActionCallService::ActionCallService(std::string alias, std::string service, json service_data)
        : Action(std::move(alias)) {
    this->service  = std::move(service);
    this->service_data = std::move(service_data);
}

ActionCallService::~ActionCallService() = default;

void ActionCallService::Do() {
    std::cout << "AcitonCallService Do" << std::endl;
}


