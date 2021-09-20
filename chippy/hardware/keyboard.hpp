#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <array>

#include <optional>

namespace chippy
{

using key = sf::Keyboard::Key;

struct keyboard
{
    // index is CHIP-8 key, Value is SFML key index
    std::array<key, 16> keymap;

    keyboard() :
        // mapping 4x4 chip 8 board to 4x4 qwerty board
        keymap
        {
            // chip-8 keys 0x0-0x3
            key::X, key::Num1, key::Num2, key::Num3,

            // chip-8 keys 0x4-0x7
            key::Q, key::W, key::E, key::A,

            // chip-8 keys 0x8-0xB
            key::S, key::D, key::Z, key::C,

            // chip-8 keys 0xC-0xF
            key::Num4, key::R, key::F, key::V
        }
    {
    }


    // should be able to report on keys 0x0-0xF
    bool pressed(const std::uint8_t key) const
    {
        return sf::Keyboard::isKeyPressed(keymap[key]);
    }

    std::optional<std::uint8_t> any() const
    {
        for (std::uint8_t key = 0; key <= 0xF; ++key)
        {
            bool isPressed = pressed(key);
            if (isPressed)
                return key;
        }
        return std::nullopt;
    }

private:
};

}

#endif