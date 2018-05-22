//
// Created by Oleg Chirukhin on 22.05.2018.
//

#ifndef NODE_NATIVE_BUFFER_DAEMON_H
#define NODE_NATIVE_BUFFER_DAEMON_H


#include "datasource.hpp"

class Daemon {
public:
    static void run();
    static void run_async();
};


#endif //NODE_NATIVE_BUFFER_DAEMON_H
