#pragma once

#include "moszir/ifstream.hpp"

#include <filesystem>
#include <iostream>

namespace aoc
{

class Solver
{
public:

    virtual ~Solver() = default;

    virtual void parse(moszir::Ifstream&) = 0;

    void parseFile(const std::string& filename)
    {
        moszir::Ifstream file(filename);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filename << '\n';
            return;
        }
        parse(file);
    }

    void parseFile(const std::filesystem::path& path)
    {
        parseFile(path.string());
    }

    virtual std::string solvePart1() = 0;
    virtual std::string solvePart2() = 0;
};

// define a templated void function that takes a type that is a subclass of Solver
template <typename SolverType>
void runSolver()
{
    static_assert(std::is_base_of<Solver, SolverType>::value, "T must be a subclass of Solver");

    SolverType solver;
    solver.parseFile(std::string("input.txt"));
    std::cout << "Part 1: " << solver.solvePart1() << '\n';
    std::cout << "Part 2: " << solver.solvePart2() << '\n';
}

} // namespace aoc
