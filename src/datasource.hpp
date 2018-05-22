#ifndef NODE_NATIVE_BUFFER_DATASOURCE_H
#define NODE_NATIVE_BUFFER_DATASOURCE_H

#include <string>
#include <sstream>
#include <deque>
#include <thread>
#include <iostream>
#include "data.hpp"
#include "udpclient.h"
#include "nodebridge.h"
#include "terminable.hpp"

//https://codereview.stackexchange.com/questions/84109/a-multi-threaded-producer-consumer-with-c11
class Buffer
{
public:
    void add(Data num) {
        while (true) {
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker, [this](){return buffer_.size() < max_buffer_size;});
            buffer_.push_back(num);
            locker.unlock();
            cond.notify_all();
            return;
        }
    }
    Data remove() {
        while (true)
        {
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker, [this](){return !buffer_.empty();});
            Data back = buffer_.back();
            buffer_.pop_back();
            locker.unlock();
            cond.notify_all();
            return back;
        }
    }
    Buffer() {}
private:
    std::mutex mu;
    std::condition_variable cond;
    std::deque<Data> buffer_;
    const unsigned int max_buffer_size = INT_MAX;

public:
    Buffer(const unsigned int max_buffer_size) : max_buffer_size(max_buffer_size) {}
};


class Producer: public Terminable
{
public:
    unsigned int latency = 50;
    Producer(Buffer* buffer, const unsigned int latency)
    {
        this->buffer_ = buffer;
        this->latency = latency;
    }
    void run() {
        while (!terminating()) {
            const Data &data = UDPClient::next_data();
            buffer_->add(data);
            std::this_thread::sleep_for(std::chrono::milliseconds(latency));
        }
    }
private:
    Buffer *buffer_;
};

class Consumer: public Terminable
{
public:
    unsigned int latency = 50;
    Consumer(Buffer* buffer, const unsigned int latency)
    {
        this->buffer_ = buffer;
        this->latency = latency;
    }
    void run() {
        while (!terminating()) {
            Data num = buffer_->remove();
            NodeBridge::consume(num);
            std::this_thread::sleep_for(std::chrono::milliseconds(latency));
        }
    }
private:
    Buffer *buffer_;
};

#endif //NODE_NATIVE_BUFFER_DATASOURCE_H
