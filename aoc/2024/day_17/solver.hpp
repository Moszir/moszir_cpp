#pragma once

#include "aoc/aoc.hpp"
#include "moszir/vector.hpp"


namespace aoc::year2024::day17
{

class Solver final : public aoc::Solver
{
public:

    void parse(moszir::Ifstream& in) override
    {
        std::string dummy, dummy2;
        in >> dummy >> dummy2 >> a_; // "Register", "A:", value
        in >> dummy >> dummy2 >> b_;
        in >> dummy >> dummy2 >> c_;
        in >> dummy; // "Program:"
        in >> program_;
        while (!in.isEndOfLineNext())
        {
            char comma;
            in >> comma >> program_;
        }
    }

    std::string solvePart1() override
    {
        simulate();
        return output_.toString(',');
    }

    std::string solvePart2() override
    {
        return std::to_string(recursiveSolve(static_cast<int64_t>(program_.size()) - 1, 0));
    }

private:

    uint64_t a_ = 0;
    uint64_t b_ = 0;
    uint64_t c_ = 0;
    moszir::Vector<uint64_t> program_;
    std::size_t instructionPointer_ = 0u;
    moszir::Vector<uint64_t> output_;

    void simulate()
    {
        output_.clear();
        instructionPointer_ = 0u;
        while (instructionPointer_ < program_.size())
        {
            switch (program_[instructionPointer_])
            {
            case 0: // "adv"
                a_ >>= combo();
                break;
            case 1: // "bxl"
                b_ ^= program_[instructionPointer_+1];
                break;
            case 2: // "bst"
                b_ = combo() % 8u;
                break;
            case 3: // "jnz"
                if (a_ != 0)
                {
                    instructionPointer_ = program_[instructionPointer_+1]; // Will be 0 of course...
                    continue;
                }
                break;
            case 4: // "bxc"
                b_ ^= c_;
                break;
            case 5: // "out"
                output_.push_back(combo() % 8u);
                break;
            case 6: // "bdv"
                b_ = a_ >> combo();
                break;
            case 7: // "cdv"
                c_ = a_ >> combo();
                break;
            default:
                throw std::runtime_error("Unknown instruction");
            }
            instructionPointer_ += 2u;
        }
    }

    [[nodiscard]] uint64_t combo() const
    {
        switch (program_[instructionPointer_+1])
        {
        case 4u: return a_;
        case 5u: return b_;
        case 6u: return c_;
        default: return program_[instructionPointer_+1];
        }
    }

    // Recursive solution
    // We will only go `program.size()` deep, so no need to manage it with a stack.
    int64_t recursiveSolve(const int64_t n, int64_t a)
    {
        if (n == -1)
        {
            return a;
        }

        a <<= 3;
        for (int x = 0; x < 8; ++x)
        {
            a_ = a + x;
            simulate();
            if (output_.equals(program_.slice_view(n)))
            {
                if (const auto s = recursiveSolve(n - 1, a + x); s != -1)
                {
                    return s;
                }
            }
        }
        return -1;
    }

};

} // namespace aoc::year2024::day17
