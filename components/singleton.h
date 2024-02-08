//
// Created by talgarr on 07/02/24.
//

#ifndef DISTRIBUTED_AUTOMATIONS_SINGLETON_H
#define DISTRIBUTED_AUTOMATIONS_SINGLETON_H


class MySingleton{
public:
    static MySingleton& getInstance(){
        static MySingleton instance;
        // volatile int dummy{};
        return instance;
    }
private:
    MySingleton()= default;
    ~MySingleton()= default;
};

#endif //DISTRIBUTED_AUTOMATIONS_SINGLETON_H
