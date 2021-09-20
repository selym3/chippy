#ifndef __FONT_HPP__
#define __FONT_HPP__

#include <cstdint>
#include <array>

namespace chippy
{

// digits provided by chip 8 to draw with
constexpr std::uint8_t kFontSpriteCount = 16; 

using font_sprite = std::array<std::uint8_t, 5>;
using font = std::array<font_sprite, kFontSpriteCount>;

constexpr font kFont = 
{
    font_sprite{ 0xF0, 0x90, 0x90, 0x90, 0xF0 }, // 0
    font_sprite{ 0x20, 0x60, 0x20, 0x20, 0x70 }, // 1
    font_sprite{ 0xF0, 0x10, 0xF0, 0x80, 0xF0 }, // 2
    font_sprite{ 0xF0, 0x10, 0xF0, 0x10, 0xF0 }, // 3
    font_sprite{ 0x90, 0x90, 0xF0, 0x10, 0x10 }, // 4
    font_sprite{ 0xF0, 0x80, 0xF0, 0x10, 0xF0 }, // 5
    font_sprite{ 0xF0, 0x80, 0xF0, 0x90, 0xF0 }, // 6
    font_sprite{ 0xF0, 0x10, 0x20, 0x40, 0x40 }, // 7
    font_sprite{ 0xF0, 0x90, 0xF0, 0x90, 0xF0 }, // 8
    font_sprite{ 0xF0, 0x90, 0xF0, 0x10, 0xF0 }, // 9
    font_sprite{ 0xF0, 0x90, 0xF0, 0x90, 0x90 }, // A
    font_sprite{ 0xE0, 0x90, 0xE0, 0x90, 0xE0 }, // B
    font_sprite{ 0xF0, 0x80, 0x80, 0x80, 0xF0 }, // C
    font_sprite{ 0xE0, 0x90, 0x90, 0x90, 0xE0 }, // D
    font_sprite{ 0xF0, 0x80, 0xF0, 0x80, 0xF0 }, // E
    font_sprite{ 0xF0, 0x80, 0xF0, 0x80, 0x80 }, // F
};

}

#endif