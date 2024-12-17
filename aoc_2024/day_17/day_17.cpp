#include <array>
#include <iostream>
#include <vector>

// Parsed "input.txt" with my eyes...
static constexpr int64_t A = 52'042'868;
static const std::array program = {2, 4, 1, 7, 7, 5, 0, 3, 4, 4, 1, 7, 5, 5, 3, 0};

std::vector<int64_t> solve(int64_t a)
{
    std::vector<int64_t> output;
    while (a != 0)
    {
        output.push_back((a ^ a >> (a & 7 ^ 7)) & 7);
        a >>= 3;
    }
    return output;
}

// std::vector<int64_t> solve(int64_t a)
// {
//     int64_t b = 0;
//     int64_t c = 0;
//     std::vector<int64_t> output;
//
//     while (a != 0)
//     {
//         b = a % 8;               // 2 4  | bst 4  | b = combo(4) % 8 = a % 8
//         b ^= 7;                  // 1 7  | bxl 7  | b ^= 7
//         c = a >> b;              // 7 5  | cdv 5  | c = a / (2 ** b)
//         a >>= 3;                 // 0 3  | adv 3  | a /= 2 ** 3
//         b ^= c;                  // 4 4  | bxc
//         b ^= 7;                  // 1 7  | bxl 7  | b ^= 7
//         output.push_back(b % 8); // 5 5  | out 5  | out B % 8
//                                  // 3 0  | jnz 0  | if a != 0: goto 0
//     }
//     return output;
// }

// std::vector<int64_t> solve(int64_t a)
// {
//     int64_t b = 0;
//     int64_t c = 0;
//     const auto combo = [&a, &b, &c](const int64_t arg)
//     {
//         if (arg < 4) return arg;
//         if (arg == 4) return a;
//         if (arg == 5) return b;
//         if (arg == 6) return c;
//         return -1LL;
//     };
//     size_t ip = 0u;
//     std::vector<int64_t> output;
//
//     while (ip < program.size())
//     {
//         const auto arg = program[ip + 1];
//         switch (program[ip])
//         {
//         case 0: { a /= 1 << combo(arg); break; }
//         case 1: { b ^= arg; break; }
//         case 2: { b = combo(arg) % 8; break; }
//         case 3: { if (a != 0) { ip = arg; continue; } break; }
//         case 4: { b ^= c; break; }
//         case 5: { output.push_back(combo(arg) % 8); break; }
//         case 6: { b = a / (1 << combo(arg)); break; }
//         case 7: { c = a / (1 << combo(arg)); break; }
//         default: throw std::runtime_error("Invalid opcode");
//         }
//         ip += 2;
//     }
//     return output;
// }

int64_t recursiveRun(size_t n, int64_t a)
{
    if (n == -1)
    {
        return a;
    }

    a <<= 3;
    for (int x = 0; x < 8; ++x)
    {
        if (const auto result = solve(a + x);
            result.size() == program.size() - n
            && std::equal(result.begin(), result.end(), std::next(program.begin(), static_cast<ptrdiff_t>(n))))
        {
            if (const auto s = recursiveRun(n - 1, a + x); s != -1)
            {
                return s;
            }
        }
    }
    return -1;
}

int main()
{
    for (const auto& r : solve(A))
    {
        std::cout << r << ',';
    }
    std::cout << '\n'; // 2,1,0,1,7,2,5,0,3.
    std::cout << recursiveRun(program.size() - 1, 0) << '\n'; // 267'265'166'222'235
    return 0;
}
