//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGER_HPP
#define CPP_TRIGGER_HPP

#include <string>
#include <utility>
using namespace std;

class Trigger {
protected:
    string alias;
public:
    explicit Trigger(string alias);
};

#endif //CPP_TRIGGER_HPP