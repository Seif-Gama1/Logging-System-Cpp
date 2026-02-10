#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <memory>

class ThreadPool{
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> taskQueue;
        std::mutex queueMutex;
        std::condition_variable cv;
        bool stop = false;

        void runWorker(){
            while (true){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    cv.wait(lock, [this](){ return stop || !taskQueue.empty(); });

                    if (stop && taskQueue.empty())
                        return;

                    task = std::move(taskQueue.front());
                    taskQueue.pop();
                }
                task();
            }
        }

    public:
        explicit ThreadPool(std::size_t numThreads) {
            for (std::size_t i = 0; i < numThreads; ++i){
                workers.emplace_back([this]() { runWorker(); });
            }
        }

        ~ThreadPool(){
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                stop = true;  // signal shutdown
            }
            cv.notify_all();  // wake up all threads

            for (auto& worker : workers){
                if (worker.joinable())
                    worker.join();
            }
        }

        // Non-copyable / non-movable
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;
        ThreadPool& operator=(ThreadPool&&) = delete;

        bool submit(std::function<void()> func){
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                if (stop)
                    return false;
                taskQueue.emplace(std::move(func));
            }
            cv.notify_one();
            return true;
        }
};
