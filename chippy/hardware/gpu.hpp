#ifndef __GPU_HPP__
#define __GPU_HPP__

#include <SFML/Graphics.hpp>
#include <vector>

namespace chippy
{

struct sprite
{
    std::uint8_t x, y;
    std::vector<char> bytes;
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
        for (std::size_t row = sprite.y; row < sprite.bytes.size(); ++row)
        {
            // to avoid this loop, i can change the vector bits to be 
            // a vecotr char, but then reading and creating the loop is annoying
            for (std::size_t col = sprite.x; col < 8; ++col)
            {
                auto index = row * cols + col;
                auto value = bits[index];
                bits[index] = value ^ (sprite.bytes[row]&col);
            }
        }
        return collision;
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
        for (int i = 0; i < kPixelCols; ++i)
            frame.bits[i] = true;
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