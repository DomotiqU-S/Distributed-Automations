//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_ACTIONDELAY_HPP
#define CPP_ACTIONDELAY_HPP
#include "Action.hpp"


class ActionDelay : public Action {
public:
    ActionDelay(std::string alias, time_t delay);
    ~ActionDelay() override;
    void Do() override;

    time_t delay;
};


#endif //CPP_ACTIONDELAY_HPP
