//
// Created by talgarr on 01/02/24.
//

#ifndef DISTRIBUTED_SERVER_ACTIONCALLSERVICE_HPP
#define DISTRIBUTED_SERVER_ACTIONCALLSERVICE_HPP

#include "Action.hpp"

class ActionCallService : public Action {
public:
    ActionCallService(string alias, string service, string service_data);
    ~ActionCallService() override;
    void Do() override;

protected:
    string service;
    string service_data;
};


#endif //DISTRIBUTED_SERVER_ACTIONCALLSERVICE_HPP
