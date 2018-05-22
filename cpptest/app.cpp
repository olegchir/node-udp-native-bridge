#include <iostream>
#include "../src/daemon.hpp"

int main() {
    Daemon daemon;

    daemon.start();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Asking Daemon to Stop" << std::endl;
    daemon.stop();

    std::cout << "Asking Daemon to Join" << std::endl;
    daemon.join();

    std::cout << "Bye!" << std::endl;
    return 0;
}