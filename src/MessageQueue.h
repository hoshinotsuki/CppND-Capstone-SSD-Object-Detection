#ifndef _MESSAGEQUEUE_H
#define _MESSAGEQUEUE_H

#include <mutex>
#include <deque>
#include <condition_variable>

template <typename T>
class MessageQueue
{
  public:

    // return and remove the first message in the queue
    T receive()
    {
        // unique_lock for condition_variable to wait
        std::unique_lock<std::mutex> ulock(_mutex);

        // wait until there is a message in the queue 
        _cond.wait(ulock, [this]{ return !_messages.empty(); });

        // using move semantics to receive and remove the first msg in the queue
        T msg = std::move(_messages.front());
        _messages.pop_front();

        return msg;
    }


    // add a message at the back of queue
    void send(T &&msg)
    {
        // locks the mutex
        std::lock_guard<std::mutex> ulock(_mutex);

        _messages.push_back(std::move(msg));

        // wakes up a waiting thread blocked in the receive() method
        _cond.notify_one();
    }

    // current size of the message queue
    size_t getSize()
    {
        return _messages.size();
    }
    
    int getTotal()
    {
        // if _total = 0, sending is unfinished
        // if _total > 0, the total number of frames being sent
        std::lock_guard<std::mutex> ulock(_mutex);
        return _total;
    }
    void setTotal(int total)
    {
        std::lock_guard<std::mutex> ulock(_mutex);
        _total = total;
    }

  private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _messages;
    int _total = 0;
};

#endif