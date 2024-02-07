//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGER_HPP
#define CPP_TRIGGER_HPP

#include <string>
#include <utility>
#include <condition_variable>

using namespace std;

class Trigger {
protected:
    string alias;

public:
    explicit Trigger(string alias);

    virtual void SetTrigger(condition_variable *cv_mother, mutex *cv_m_mother) = 0;
};

#endif //CPP_TRIGGER_HPP
