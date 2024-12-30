# DynamicThread

- Dynamic Thread for Modern C++

## Usage
```cpp
// [1] Create multi-threaded jobs
class ExampleTask : ThreadTask {
public:
    void performTask() override {
        // Starting from here, you can start doing things in multi-threads
        static int counter = 0;
        std::cout << "ExampleTask is running: " << counter++ << "\n";
    }
};

int main() {
    DynamicThread dt;
    ExampleTask task;

    // [2] Setting the interval for work functions within multi-threads (default 500ms)
    dt.setInterval(std::chrono::milliseconds(500));

    // [3] Registering member functions and Starting multi-threads
    dt.start(&ExampleTask::performTask, &task);

    std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait for the main thread to run for 5 seconds
	
    dt.stop(); // Stop multi-threads

    std::cout << "Thread stopped.\n";

    return 0;
}
```
