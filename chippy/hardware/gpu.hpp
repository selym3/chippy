#ifndef __GPU_HPP__
#define __GPU_HPP__

#include <cstdint>

#include <SFML/Graphics.hpp>
#include <vector>

#include <bitset>
#include <ostream>

namespace chippy
{

struct sprite
{
    std::uint16_t x, y;
    std::vector<std::uint8_t> bytes;

    friend std::ostream& operator<<(std::ostream&os, const sprite& s)
    {
        std::cout << "Sprite (\n\tx: " << s.x << ", y: " << s.y;
        std::cout << "\n\tbytes:\n";
        for (auto byte : s.bytes)
            std::cout << "\t\t" << std::bitset<8>(byte) << "\n";
        std::cout << ")";

        return os;
    }
};

// construct simple frame buffer
constexpr std::size_t kPixelRows = 32;
constexpr std::size_t kPixelCols = 64;

constexpr float kPixelWidth = 10.0;
constexpr float kPixelHeight = 10.0;

struct frame : sf::Drawable
{
    std::vector<bool> bits;
    std::size_t cols, rows;
    float colsize, rowsize;

    frame(std::size_t cols, std::size_t rows, float colsize, float rowsize) :
        cols { cols }, rows { rows }, colsize { colsize }, rowsize { rowsize }
    {
        bits.reserve(cols * rows);

        // find the actual function to fill vectors
        for (int i = 0; i < cols * rows; ++i)
            bits.push_back(false);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (float row = 0; row < rows; ++row)
        {
            for (float col = 0; col < cols; ++col)
            {
                bool on = bits[row * cols + col];
                if (on)
                {
                    sf::RectangleShape pixel;
                    pixel.setPosition(col * colsize, row * rowsize);
                    pixel.setSize({ colsize, rowsize });
                    pixel.setFillColor(sf::Color::White);

                    // TODO: batch draw rectangles
                    target.draw(pixel);
                }
            }
        }
    }

    // mutates the frame and returns if there was a collision
    int xoreq(const sprite& sprite) 
    {
        int collision = 0;
        for (std::size_t row = 0; row < sprite.bytes.size(); ++row)
        {
            for (std::size_t col = 0; col < 8; ++col)
            {   
                // looped row & col
                auto rl = (row+sprite.y)%rows,
                     cl = (col+sprite.x)%cols;

                // read from frame
                auto index = rl * cols + cl;
                bool bit = bits[index];

                // read from sprite
                auto bitmask = 1<<(7-col);
                bool newbit = (sprite.bytes[row]&bitmask) > 0;

                // update frame
                bool xorbit = bit^newbit;
                bits[index] = xorbit;

                // update collision
                collision |= (bit&&!xorbit);
            }
        }
        return collision;
    }

    friend std::ostream& operator<<(std::ostream& os, const frame& fr)
    {
        for (int row = 0; row < fr.rows; ++row)
        {
            for (int col = 0; col < fr.cols; ++col)
                std::cout << fr.bits[row * fr.cols + col];
            std::cout << "\n";
        }
        return os;
    }
};

constexpr std::size_t kScreenWidth = kPixelWidth * kPixelCols;
constexpr std::size_t kScreenHeight = kPixelHeight * kPixelRows;

struct gpu
{
    sf::RenderWindow window;
    frame frame;

    gpu() :
        window 
        { 
            sf::VideoMode(kScreenWidth, kScreenHeight),
            "CHIP-8",
            sf::Style::None
        },
        frame { kPixelCols, kPixelRows, kPixelWidth, kPixelHeight }
    {
    }

    void clear() 
    {
        window.clear(sf::Color::Black);
        for (int i = 0; i < frame.bits.size(); ++i)
            frame.bits[i] = false;
    }

    void draw()
    {
        window.clear(sf::Color::Black);
        window.draw(frame);
        window.display();
    }
};

}

#endif