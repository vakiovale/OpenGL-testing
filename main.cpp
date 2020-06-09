#include <thread>

#include "src/app.h"

void runApplication() {
    try {
        App app;
        app.run();
    } catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}

int main() {
    std::thread applicationThread(runApplication);
    applicationThread.join();
}
