#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>

namespace chippy
{

using ms = std::chrono::milliseconds::rep;

struct timer
{
    ms time;

    timer()
        : time{now()} 
    {
    }

    ms now() const 
    {
        return 
            std::chrono::system_clock::now().time_since_epoch() / 
            std::chrono::milliseconds(1);
    }

    ms elapsed() const 
    {
        return now()-time;
    }

    ms reset()
    {
        ms _now = now();
        ms elapsed = _now-time;
        
        time = _now;
        return elapsed;
    }

};

}


#endif