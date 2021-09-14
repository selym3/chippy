#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <cstdint>
#include <array>

namespace chippy
{

template <std::size_t Size>
struct stack
{
    std::array<std::uint16_t, Size> buffer;
    std::uint16_t top = 0;


    void push(std::uint16_t value) 
    {
        buffer[top++] = value;
    }

    std::uint16_t pop() 
    {
        --top;
        return buffer.back(); 
    }

};

}

#endif