#ifndef MATRIX_BUFF_CHANNEL_BUFFERED_CHANNEL_H
#define MATRIX_BUFF_CHANNEL_BUFFERED_CHANNEL_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class BufferedChannel
{
private:
    std::queue<T> queue;
    int buffer_size{};
    bool isOpened;
    std::mutex mutex;
    std::condition_variable conditionVariable;
public:
    explicit BufferedChannel(int buffer_size)
    {
        this->buffer_size = buffer_size;
        isOpened = true;
    }

    void Send(T value)
    {
        std::unique_lock<std::mutex> locker(mutex);
        conditionVariable.wait(locker, [&]()
        { return queue.size() < buffer_size || !isOpened; });
        if (!isOpened)
        {
            throw std::runtime_error("Thread is closed!");
        }
        queue.push(value);
        locker.unlock();
        conditionVariable.notify_one();
    }

    std::pair<T, bool> Recv()
    {
        std::unique_lock<std::mutex> locker(mutex);
        conditionVariable.wait(locker, [&] {return !queue.empty() || (!isOpened && queue.empty()); });
        if (!isOpened && queue.empty())
        {
            return std::pair<T, bool>(T(), false);
        }
        T value(queue.front());
        queue.pop();
        locker.unlock();
        conditionVariable.notify_one();
        return std::pair<T, bool>(value, true);
    }

    void Close()
    {
        std::lock_guard<std::mutex> lockGuard(mutex);
        isOpened = false;
        conditionVariable.notify_all();
    }
};

#endif //MATRIX_BUFF_CHANNEL_BUFFERED_CHANNEL_H