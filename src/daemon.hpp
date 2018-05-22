//
// Created by Oleg Chirukhin on 22.05.2018.
//

#ifndef NODE_NATIVE_BUFFER_DAEMON_H
#define NODE_NATIVE_BUFFER_DAEMON_H


#include "datasource.hpp"

class Daemon {
public:
    void start();
    void stop();
    void join();

    Daemon();
    virtual ~Daemon();

private:
    Buffer *buffer;
    Producer *producer;
    Consumer *consumer;
    std::thread *producer_thread;
    std::thread *consumer_thread;
};


#endif //NODE_NATIVE_BUFFER_DAEMON_H
