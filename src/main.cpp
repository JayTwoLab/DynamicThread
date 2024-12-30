#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>

#include "DynamicThread.h"

// Crreate a multi-threaded task
class ExampleTask : j2::ThreadTask {
public:
    void performTask() override {
        // Starting from here, you can start doing things in multi-threads
        static int counter = 0;
        std::cout << "ExampleTask is running: " << counter++ << "\n";
    }
};

int main() {
    j2::DynamicThread dt;
    ExampleTask task;

    // Setting the interval for work functions within multi-threads (default 100ms)
    dt.setInterval(std::chrono::milliseconds(500));

    // Registering member functions and starting multi-threads
    dt.start(&ExampleTask::performTask, &task);

    std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait for the main thread to run for 5 seconds
	
    dt.stop(); // Stop multi-threads

    std::cout << "Thread stopped.\n";

    return 0;
}
