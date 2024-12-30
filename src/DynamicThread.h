#ifndef DYNAMICTHREAD_H
#define DYNAMICTHREAD_H

#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>

namespace j2 {

class DynamicThread {
protected:
    std::thread workerThread;          // Thread Object
    std::atomic<bool> running;         // Thread execution status flag
    std::function<void()> task;        // Action Functions to Run
    std::chrono::milliseconds interval; // Job interval

    void threadFunction() {
        while (running.load()) {
            if (task) {
                task(); // Performing a task
            }
            std::this_thread::sleep_for(interval); // Adjusting the Job Interval
        }
    }

public:
    DynamicThread()
        : running(false), task(nullptr), interval(100) {} // Set default interval of 100 ms

    ~DynamicThread() {
        stop(); // End Thread on Object Destruction
    }

    // Operation interval setting function
    void setInterval(std::chrono::milliseconds newInterval) {
        interval = newInterval;
    }

    // Start Thread (member or regular functions can be registered)
    template <typename Callable, typename... Args>
    void start(Callable&& func, Args&&... args) {
        if (running.load()) {
            std::cerr << "Thread is already running.\n";
            return;
        }

        // Use std::bind to combine a member function or normal function with a factor
        task = std::bind(std::forward<Callable>(func), std::forward<Args>(args)...);
        running.store(true);
        workerThread = std::thread(&DynamicThread::threadFunction, this);
    }

    // Stop Threads
    void stop() {
        if (running.load()) {
            running.store(false);
            if (workerThread.joinable()) {
                workerThread.join(); // Wait for the thread to end
            }
        }
    }

    // Verify that it is running
    bool isRunning() const {
        return running.load();
    }
};

// Multi-threaded Task Base Classes
class ThreadTask {
protected:
    virtual void performTask() = 0;
};

} // End of namespace j2

#endif // DYNAMICTHREAD_H
