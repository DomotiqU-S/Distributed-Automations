//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_ACTIONDELAY_HPP
#define CPP_ACTIONDELAY_HPP
#include "Action.hpp"


class ActionDelay : public Action {
protected:
    time_t delay;

public:
    ActionDelay(string alias, time_t delay);
    ~ActionDelay() override;
    void Do() override;

};

#endif //CPP_ACTIONDELAY_HPP
