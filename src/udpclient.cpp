#include <cstdlib>
#include <iostream>
#include "udpclient.h"

Data UDPClient::next_data() {
    int num = std::rand() % 100;
    std::cout << "Produced: " << num << std::endl;\
    return Data(num);
}