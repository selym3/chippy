#ifndef __OPCODE_HPP__
#define __OPCODE_HPP__

#include <cstdint>
#include <ostream>

namespace chippy
{

struct opcode
{
    /**
     * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
     * 
     * opcodes are 2 bytes (4 nibbles)
     * 
     * the highest 4 bits is always a constant 0x0-0xF
     * the remaining 12 bits can be a combination of:
     *  - "nnn" -> A 12-bit value, the lowest 12 bits of the instruction
     *  - "n" -> A 4-bit value, the lowest 4 bits of the instruction
     *  - "x" -> A 4-bit value, the lower 4 bits of the high byte of the instruction
     *  - "y" -> A 4-bit value, the upper 4 bits of the low byte of the instruction
     *  - "kk" -> An 8-bit value, the lowest 8 bits of the instruction
     *  - some constant value specific to that opcode
     */

    const std::uint16_t _opcode;

    constexpr inline opcode(std::uint16_t _opcode) :
        _opcode{_opcode}
    {
    }

    constexpr inline std::uint16_t get() const
    { return _opcode; }

    friend std::ostream& operator<<(std::ostream& os, const opcode& op)
    { 
        os << "0x";
        os << std::hex;
        // separate into nibbles to get leading zeroes
        os << op.extract(3); 
        os << op.extract(2);
        os << op.extract(1);
        os << op.extract(0);
        os << ""; // necessary for some reason
        os << std::dec; 
        return os;
    }

    /****************
     * PARSE OPCODE *
     ****************/

    // highest 4 bits
    constexpr inline std::uint8_t id() const
    { return extract(3); }

    // nnn
    constexpr inline std::uint16_t addr() const
    { return extract(0, 2); }

    // kk 
    constexpr inline std::uint8_t byte() const
    { return extract(0, 1); }

    // n
    constexpr inline std::uint8_t nibble() const
    { return extract(0); }

    // x
    constexpr inline std::uint8_t x() const
    { return extract(2); }

    // y 
    constexpr inline std::uint8_t y() const
    { return extract(1); }

    /******************* 
     * EXTRACT NIBBLES *
     *******************/

    constexpr inline std::uint16_t extract(std::uint8_t ln, std::uint8_t hn) const
    {
        std::uint16_t norm = 4 * ln;

        // fix the F's in the mask
        std::uint16_t mask = (1<<(4 * (hn-ln+1))) - 1;
        // fix the 0's in the mask
        mask<<=norm;
        
        return (_opcode&mask)>>norm;
    }

    constexpr inline std::uint16_t extract(std::uint8_t nibble) const
    {
        return extract(nibble, nibble);
    }

};


}

#endif