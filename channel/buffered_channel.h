#ifndef BUFFERED_CHANNEL_BUFFERED_CHANNEL_H
#define BUFFERED_CHANNEL_BUFFERED_CHANNEL_H

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
        if (!isOpened)
        {
            throw std::runtime_error("Thread is closed!");
        }
        conditionVariable.wait(locker, [&] { return queue.size() != buffer_size;});
        queue.push(value);
        std::cout << "Value " << value << " has been added to channel.\n";
        locker.unlock();
        conditionVariable.notify_one();
    }

    std::pair<T, bool> Recv()
    {
        std::unique_lock<std::mutex> locker(mutex);
        conditionVariable.wait(locker,[&] {return !queue.empty(); });
        T value = queue.front();
        queue.pop();
        std::cout << "Value " << value << " has been deleted.\n" << std::endl;
        locker.unlock();
        conditionVariable.notify_one();
        return std::pair<T, bool>(value, isOpened);
    }

    void Close()
    {
        std::lock_guard<std::mutex> lockGuard(mutex);
        isOpened = false;
        std::cout << "Channel has been closed.\n" << std::endl;
        conditionVariable.notify_one();
    }
};

#endif //BUFFERED_CHANNEL_BUFFERED_CHANNEL_H