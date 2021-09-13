#include "./cpu.hpp"

using namespace chippy;

opcode cpu::get_opcode() const
{
    char upper = memory[kFreeStart + (pc + 0)];
    char lower = memory[kFreeStart + (pc + 1)];

    std::uint16_t data =
        (static_cast<unsigned char>(upper) << 8) +
        (static_cast<unsigned char>(lower) << 0);

    return opcode{data};
}

void cpu::cycle()
{
    auto opcode = get_opcode();
    auto id = opcode.extract(3);

    std::cout << opcode << " " << id << " \n";

    handle_opcode(*this, opcode);
    this->pc += 2;
}

void cpu::handle_opcode(cpu &cpu, opcode op)
{
    switch (op.id())
    {

    case 0x0:
    {
        switch (op.get())
        {
        case 0x00E0:
        {
            break;
        }

        case 0x00EE:
        {
            break;
        }

        default:
        {
            std::cout << "ignored\n";
            break;
        }
        }

        break;
    }

    case 0x1:
    {
        std::cout << op << "\n";
        break;
    }

    case 0x2:
    {
        std::cout << op << "\n";
        break;
    }

    case 0x3:
    {
        if (cpu.v[op.x()] == op.byte())
            cpu.pc += 2;

        break;
    }

    case 0x4:
    {
        if (cpu.v[op.x()] != op.byte())
            cpu.pc += 2;

        break;
    }

    case 0x5:
    {
        if (cpu.v[op.x()] == cpu.v[op.y()])
            cpu.pc += 2;

        break;
    }

    case 0x6:
    {
        cpu.v[op.x()] = op.byte();
        break;
    }

    case 0x7:
    {
        cpu.v[op.x()] += op.byte();
        break;
    }

    case 0x8:
    {
        // for conveience
        std::uint8_t x = op.x();
        std::uint8_t y = op.y();

        // lowest nibble is type of register operation
        auto type = op.extract(0);
        switch (type)
        {
        case 0x0:
        {
            cpu.v[x] = cpu.v[y];
            break;
        }

        case 0x1:
        {
            cpu.v[x] |= cpu.v[y];
            break;
        }

        case 0x2:
        {
            cpu.v[x] &= cpu.v[y];
            break;
        }

        case 0x3:
        {
            cpu.v[x] ^= cpu.v[y];
            break;
        }

        case 0x4:
        {
            std::uint16_t add = cpu.v[x] + cpu.v[y];
            cpu.v[0xF] = add > 255;
            cpu.v[x] = static_cast<std::uint8_t>(add & 0x00FF);
            break;
        }

        case 0x5:
        {
            cpu.v[0xF] = cpu.v[x] > cpu.v[y];
            cpu.v[x] -= cpu.v[y];
            break;
        }

        case 0x6:
        {
            cpu.v[0xF] = cpu.v[x] & 1;
            cpu.v[x] >>= 1;
            break;
        }

        case 0x7:
        {
            cpu.v[0xF] = cpu.v[y] > cpu.v[x];
            cpu.v[x] = cpu.v[y] - cpu.v[x];
            break;
        }

        case 0xE:
        {
            auto msb = 0b10000000;
            cpu.v[0xF] = ((cpu.v[x] & msb) >> 7);
            cpu.v[x] <<= 1;
            break;
        }

        default:
        {
            std::cout << "ignored\n";
            break;
        }
        }

        break;
    }

    case 0x9:
    {
        std::cout << op << "\n";
        break;
    }

    case 0xA:
    {
        std::cout << op << "\n";
        break;
    }

    case 0xB:
    {
        std::cout << op << "\n";
        break;
    }

    case 0xC:
    {
        std::cout << op << "\n";
        break;
    }

    case 0xD:
    {
        std::cout << op << "\n";
        break;
    }

    case 0xE:
    {
        std::cout << op << "\n";
        break;
    }

    case 0xF:
    {
        std::cout << op << "\n";
        break;
    }
    }
};
