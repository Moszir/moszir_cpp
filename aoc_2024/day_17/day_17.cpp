#include "moszir/vector.hpp"


// Parsed "input.txt" with my eyes...
static constexpr int64_t A = 52'042'868;
static const moszir::Vector<int64_t> program{2, 4, 1, 7, 7, 5, 0, 3, 4, 4, 1, 7, 5, 5, 3, 0};


// while (a != 0)
// {
//     b = a % 8;               // 2 4  | bst 4  | b = combo(4) % 8 = a % 8
//     b ^= 7;                  // 1 7  | bxl 7  | b ^= 7
//     c = a >> b;              // 7 5  | cdv 5  | c = a / (2 ** b)
//     a >>= 3;                 // 0 3  | adv 3  | a /= 2 ** 3
//     b ^= c;                  // 4 4  | bxc
//     b ^= 7;                  // 1 7  | bxl 7  | b ^= 7
//     output.push_back(b % 8); // 5 5  | out 5  | out B % 8
//                              // 3 0  | jnz 0  | if a != 0: goto 0
// }

// Squashed this into one line for fun...
moszir::Vector<int64_t> solve(int64_t a)
{
    moszir::Vector<int64_t> output;
    while (a != 0)
    {
        output.push_back((a ^ a >> (a & 7 ^ 7)) & 7);
        a >>= 3;
    }
    return output;
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
        if (const auto result = solve(a + x); result.equal(program.slice(n)))
        {
            if (const auto s = recursiveSolve(n - 1, a + x); s != -1)
            {
                return s;
            }
        }
    }
    return -1;
}

int main()
{
    solve(A).print(',') << '\n'; // 2,1,0,1,7,2,5,0,3
    std::cout << recursiveSolve(static_cast<int64_t>(program.size()) - 1, 0) << '\n'; // 267'265'166'222'235
    return 0;
}
