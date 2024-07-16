#include "ThreadPool.h"

ThreadPool::ThreadPool() : m_MaxThreads(0), m_MinThreads(0), m_MaxTasks(0),
running(false) {

}

void ThreadPool::initThreadPool(int _minThreads, int _maxThreads, int _maxTasks) {
    if (_minThreads > 0) {
        m_MinThreads = _minThreads;
        if (_minThreads < _maxThreads) {
            m_MaxThreads = _maxThreads;
            m_MaxTasks = _maxTasks;
        }
    }
}

void ThreadPool::startThreadPool() {
    running = true;
    
    for (int i = 0; i < m_MinThreads; i++) {
        threads.emplace_back([this] {
            while (running) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(m_TaskMutex);
                    while (tasks.empty()) {
                        m_TaskNotEmptyCondition.wait(lock, [this] {
                            return !running || !tasks.empty();
                            });
                        if (!running && tasks.empty()) {
                            return;
                        }
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

template <typename... Args>
void ThreadPool::test(Args... args) {
    std::cout << "yes" << std::endl;
}

//template <typename F, typename... Args>
//std::future<typename std::result_of<F(Args...)>::type> ThreadPool::enqueue(F f, Args... args) {
//    using returntype = typename std::result_of<F(Args...)>::type;
//    std::shared_ptr<std::packaged_task<returntype()>> task = std::make_shared<std::packaged_task<returntype()>>(
//            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
//        );
//    std::future<returntype> res = task->get_future();
//    {
//        std::unique_lock<std::mutex> lock(m_TaskMutex);
//        if (!running) {
//            throw std::runtime_error("enqueue on stopped ThreadPool!");
//        }
//        tasks.emplace([task] {
//            (*task)();
//            });
//    }
//    m_TaskNotEmptyCondition.notify_one();
//    return res;
//}

ThreadPool& ThreadPool::getInstance() {
    static ThreadPool s_ThreadPool;
    return s_ThreadPool;
}