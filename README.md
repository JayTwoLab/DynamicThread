# DynamicThread

- Dynamic Thread for Modern C++ (17 or higher version)

## Usage
```cpp
// [1] Create multi-threaded jobs
class ExampleTask : j2::ThreadTask {
public:
    void performTask() override {
        // Starting from here, you can start doing things in multi-threads
        static int counter = 0;
        std::cout << "ExampleTask is running: " << counter++ << "\n";
    }
};

int main() {
    ExampleTask task;

    // [2] Create Synamic Thread	
    j2::DynamicThread dt;

    // [3] Setting the interval for work functions within multi-threads (default 500ms)
    dt.setInterval(std::chrono::milliseconds(500));

    // [4] Registering task and Starting multi-threads
    dt.start(&ExampleTask::performTask, &task);

   // Wait for the main thread to run for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5)); 
	
    dt.stop(); // Stop multi-threads

    std::cout << "Thread stopped.\n";

    return 0;
}
```
