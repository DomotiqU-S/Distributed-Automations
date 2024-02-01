//
// Created by talgarr on 01/02/24.
//

#ifndef DISTRIBUTED_SERVER_ACTIONCALLSERVICE_HPP
#define DISTRIBUTED_SERVER_ACTIONCALLSERVICE_HPP

#include "Action.hpp"
#include "../../../Library/nlohmann/json.hpp"
using json = nlohmann::json;


class ActionCallService : public Action {
public:
    ActionCallService(std::string alias, std::string service, json service_data);
    ~ActionCallService() override;
    void Do() override;

protected:
    std::string service;
    json service_data;
};


#endif //DISTRIBUTED_SERVER_ACTIONCALLSERVICE_HPP
