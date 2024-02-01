//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_CONDITION_HPP
#define CPP_CONDITION_HPP

#include <string>
using namespace std;

class Condition
{
protected:
    string alias;

public:
    explicit Condition(char *alias);
    virtual ~Condition();
    virtual bool Verify() = 0;
};

#endif //CPP_CONDITION_HPP
