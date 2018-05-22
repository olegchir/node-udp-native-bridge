//
// Created by Oleg Chirukhin on 22.05.2018.
//

#ifndef NODE_NATIVE_BUFFER_TERMINABLE_H
#define NODE_NATIVE_BUFFER_TERMINABLE_H


#include <algorithm>
#include <future>
#include <iostream>

class Terminable {
    std::promise<void> exitSignal;
    std::future<void> futureObj;

public:
    Terminable() :
        futureObj(exitSignal.get_future()) {}

    Terminable(Terminable &&obj) : exitSignal(std::move(obj.exitSignal)), futureObj(std::move(obj.futureObj)) {
        std::cout << "Move Constructor is called" << std::endl;
    }

    Terminable &operator=(Terminable &&obj) {
        std::cout << "Move Assignment is called" << std::endl;
        exitSignal = std::move(obj.exitSignal);
        futureObj = std::move(obj.futureObj);
        return *this;
    }

    virtual void run() = 0;


    // Thread function to be executed by thread
    void operator()() {
        run();
    }

    //Checks if thread is requested to terminate
    bool terminating() {
        // checks if value in future object is available
        if (futureObj.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout) {
            return false;
        }
        return true;
    }

    // Request the thread to terminate by setting value in promise object
    void terminate() {
        exitSignal.set_value();
    }
};


#endif //NODE_NATIVE_BUFFER_TERMINABLE_H
