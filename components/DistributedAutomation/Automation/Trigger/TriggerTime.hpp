//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGERTIME_HPP
#define CPP_TRIGGERTIME_HPP

#include "Trigger.hpp"

class TriggerTime : public Trigger {
protected:
    tm at{};
public:
    TriggerTime(string alias, tm at);
    void SetTrigger(condition_variable *cv_mother, mutex *cv_m_mother) override;
    ~TriggerTime();
};


#endif //CPP_TRIGGERTIME_HPP
