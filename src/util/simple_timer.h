#ifndef TIMER_H_
#define TIMER_H_
#include<functional>
#include<chrono>
#include<thread>
#include<atomic>
#include<memory>
#include<mutex>
#include<condition_variable>
class SimpleTimer{
public:
    SimpleTimer() :expired_(true), try_to_expire_(false){
    }

    SimpleTimer(const SimpleTimer& t){
        expired_ = t.expired_.load();
        try_to_expire_ = t.try_to_expire_.load();
    }
    ~SimpleTimer(){
        Expire();
        //      std::cout << "timer destructed!" << std::endl;
    }

    void StartTimer(int interval, const std::function<void()> &task, const bool& immediately = false){
        if (expired_ == false){
            //          std::cout << "timer is currently running, please expire it first..." << std::endl;
            return;
        }
        if(immediately){
            task();
        }
        expired_ = false;
        std::thread([this, interval, task](){
            int tick_interval = 100;
            int tick_time = interval / tick_interval;
            if(tick_time < 1){
                tick_time = 1;
            }
            int real_tick_time = 0;
            while (!try_to_expire_){
                // while (!try_to_expire_ && tick_time )
                std::this_thread::sleep_for(std::chrono::milliseconds(tick_interval));
                if(!try_to_expire_ && real_tick_time == tick_time){
                    task();
                    real_tick_time = 0;
                }
                real_tick_time ++;
            }
            //          std::cout << "stop task..." << std::endl;
            {
                std::lock_guard<std::mutex> locker(mutex_);
                expired_ = true;
                expired_cond_.notify_one();
            }
        }).detach();
    }

    void Expire(){
        if (expired_){
            return;
        }

        if (try_to_expire_){
            //          std::cout << "timer is trying to expire, please wait..." << std::endl;
            return;
        }
        try_to_expire_ = true;
        {
            std::unique_lock<std::mutex> locker(mutex_);
            expired_cond_.wait(locker, [this]{return expired_ == true; });
            if (expired_ == true){
                //              std::cout << "timer expired!" << std::endl;
                try_to_expire_ = false;
            }
        }
    }

    template<typename callable, class... arguments>
    void SyncWait(int after, callable&& f, arguments&&... args){

        std::function<typename std::result_of<callable(arguments...)>::type()> task
                (std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
        std::this_thread::sleep_for(std::chrono::milliseconds(after));
        task();
    }
    template<typename callable, class... arguments>
    void AsyncWait(int after, callable&& f, arguments&&... args){
        std::function<typename std::result_of<callable(arguments...)>::type()> task
                (std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        std::thread([after, task](){
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }).detach();
    }

private:
    std::atomic<bool> expired_{};
    std::atomic<bool> try_to_expire_{};
    std::mutex mutex_;
    std::condition_variable expired_cond_;
};
#endif
