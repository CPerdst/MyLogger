#pragma once
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <functional>
#include <memory>
#include <chrono>
#include <thread>
#include <queue>
#include <vector>
#include <future>

class ThreadPool {
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    int m_MaxThreads;
    int m_MinThreads;
    int m_MaxTasks;
    bool running;
    std::mutex m_TaskMutex;
    std::condition_variable m_TaskNotEmptyCondition;

public:
    void initThreadPool(int _minThread, int _maxThread, int _maxTasks);
    void startThreadPool();
    //template <typename F, typename... Args>
    //std::future<typename std::result_of<F(Args...)>::type> enqueue(F f, Args... args);
    template <typename... Args>
    void test(Args... args);
    static ThreadPool& getInstance();
    ThreadPool(ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
private:
    explicit ThreadPool();

};

