#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>

class DynamicThread {
private:
    std::thread workerThread;          // 스레드 객체
    std::atomic<bool> running;         // 스레드 실행 상태 플래그
    std::function<void()> task;        // 실행할 작업 함수
    std::chrono::milliseconds interval; // 작업 간격

    void threadFunction() {
        while (running.load()) {
            if (task) {
                task(); // 작업 수행
            }
            std::this_thread::sleep_for(interval); // 작업 간격 조정
        }
    }

public:
    DynamicThread() 
        : running(false), task(nullptr), interval(100) {} // 기본 간격 100ms 설정

    ~DynamicThread() {
        stop(); // 객체 소멸 시 스레드 종료
    }

    // 작업 간격 설정 함수
    void setInterval(std::chrono::milliseconds newInterval) {
        interval = newInterval;
    }

    // 스레드 시작 (멤버 함수 또는 일반 함수 등록 가능)
    template <typename Callable, typename... Args>
    void start(Callable&& func, Args&&... args) {
        if (running.load()) {
            std::cerr << "Thread is already running.\n";
            return;
        }

        // std::bind를 사용하여 멤버 함수 또는 일반 함수와 인자를 결합
        task = std::bind(std::forward<Callable>(func), std::forward<Args>(args)...);
        running.store(true);
        workerThread = std::thread(&DynamicThread::threadFunction, this);
    }

    // 스레드 중지
    void stop() {
        if (running.load()) {
            running.store(false);
            if (workerThread.joinable()) {
                workerThread.join(); // 스레드가 종료될 때까지 대기
            }
        }
    }

    // 실행 중인지 확인
    bool isRunning() const {
        return running.load();
    }
};

class ThreadTask {
protected: 
	virtual void performTask() = 0;
};

class ExampleTask : ThreadTask {
public:
    void performTask() override {
        static int counter = 0;
        std::cout << "ExampleTask is running: " << counter++ << "\n";
    }
};

int main() {
    DynamicThread dt;
    ExampleTask task;

    // 작업 간격 설정 (500ms)
    dt.setInterval(std::chrono::milliseconds(500));

    // 멤버 함수 등록 및 스레드 시작
    dt.start(&ExampleTask::performTask, &task);

    std::this_thread::sleep_for(std::chrono::seconds(5)); // 5초간 실행
    dt.stop(); // 스레드 중지

    std::cout << "Thread stopped.\n";

    return 0;
}
