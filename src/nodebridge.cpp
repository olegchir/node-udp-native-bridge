//
// Created by Oleg Chirukhin on 22.05.2018.
//

#include <iostream>
#include "nodebridge.h"

void NodeBridge::consume(Data data) {
    std::cout << "Consumed: " << data.x << std::endl;
}
