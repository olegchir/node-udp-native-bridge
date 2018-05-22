//
// Created by Oleg Chirukhin on 22.05.2018.
//

#include "daemon.hpp"

void Daemon::run()  {
    Buffer b(INT_MAX);
    Producer p(&b, 50);
    Consumer c(&b, 50);

    std::thread producer_thread(&Producer::run, &p);
    std::thread consumer_thread(&Consumer::run, &c);

    producer_thread.join();
    consumer_thread.join();
}

void Daemon::run_async() {
    
}
