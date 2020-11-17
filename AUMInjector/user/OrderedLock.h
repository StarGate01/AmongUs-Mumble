// Partly taken from https://stackoverflow.com/questions/14792016/creating-a-lock-that-preserves-the-order-of-locking-attempts-in-c11

#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>
#include <vector>


// This class provides a FIFO mutex
class OrderedLock
{

    public:
        OrderedLock() : locked(false) {}

        // Blocks until caller is dequeued
        void Lock()
        {
            std::unique_lock<std::mutex> acquire(cvar_lock);
            if (locked)
            {
                std::condition_variable signal;
                cvar.emplace(std::ref(signal));
                signal.wait(acquire);
                cvar.pop();
            }
            else locked = true;
        }

        // Releases the mutex
        void Unlock()
        {
            std::unique_lock<std::mutex> acquire(cvar_lock);
            if (cvar.empty()) locked = false;
            else cvar.front().get().notify_one();
        }

    private:
        std::queue<std::reference_wrapper<std::condition_variable>> cvar;
        std::mutex cvar_lock;
        bool locked;

};

// This class provides a RAII interface to the FIFO mutex
class OrderedLockRAII
{

    public:
        // Aquire mutex on creation
        OrderedLockRAII(OrderedLock& baseLock) : lock(baseLock) { lock.Lock(); }

        // Release mutex on destruction
        ~OrderedLockRAII() { lock.Unlock(); }

    private:
       OrderedLock& lock;

};