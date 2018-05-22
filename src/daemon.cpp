//
// Created by Oleg Chirukhin on 22.05.2018.
//

#include "daemon.hpp"


void Daemon::start() {
    producer_thread = new std::thread(&Producer::run, this->producer);
    consumer_thread = new std::thread(&Consumer::run, this->consumer);
//    producer_thread = new std::thread([&]() { producer->run(); });
//    consumer_thread = new std::thread([&]() { consumer->run(); });
}


void Daemon::stop() {
    producer -> terminate();
    consumer -> terminate();
}

void Daemon::join() {
    producer_thread -> join();
    consumer_thread -> join();
}

Daemon::~Daemon() {
    delete producer;
    delete consumer;
    delete producer_thread;
    delete consumer_thread;
    delete buffer;
}

Daemon::Daemon() {
    buffer = new Buffer(INT_MAX);
    producer =  new Producer(buffer, 50);
    consumer = new Consumer(buffer, 50);
}
