//
// Created by Alumno on 12/03/2018.
//

#ifndef CONCURRENCY_MSG_QUEUE_H
#define CONCURRENCY_MSG_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<class T>
class msg_queue {
private:
    std::queue<T> cola;
    mutable std::mutex mut;
    std::condition_variable cond;
public:
    msg_queue(void) : cola(), mut(), cond() {}

    ~msg_queue(void) {}

    void enqueue(T t) {
        std::lock_guard<std::mutex> lock(mut);
        cola.push(t);
        cond.notify_one();
    }

    T dequeue(void) {
        std::unique_lock<std::mutex> lock(mut);
        while (cola.empty()) {
            cond.wait(lock);
        }
        T val = cola.front();
        cola.pop();
        return val;
    }

};

#endif //CONCURRENCY_MSG_QUEUE_H