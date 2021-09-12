#ifndef __OPTYPES_HPP__
#define __OPTYPES_HPP__

#include "./opcode.hpp"
#include <functional>
#include <array>

namespace chippy
{
    class cpu;
    
    using OpHandler = std::function<void(cpu&, opcode)>;
    using Dispatcher = std::array<OpHandler, 16>;
}

#endif