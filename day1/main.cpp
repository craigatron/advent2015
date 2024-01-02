#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

int part1(char *file)
{
    ifstream input_file(file);
    if (!input_file)
    {
        throw std::invalid_argument("invalid file");
    }
    string line;
    getline(input_file, line);

    auto left_parens = std::ranges::count(line, '(');
    return left_parens - (line.length() - left_parens);
}

int part2(char *file)
{
    ifstream input_file(file);
    if (!input_file)
    {
        throw std::invalid_argument("invalid file");
    }
    string line;
    getline(input_file, line);

    auto floor = 0;
    auto pos = 1;
    for (char &c : line)
    {
        if (c == '(')
        {
            floor += 1;
        }
        else
        {
            floor -= 1;
        }
        if (floor == -1)
        {
            break;
        }
        pos += 1;
    }

    return pos;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "usage: " << argv[0] << " [data_file.txt]" << endl;
        return EXIT_FAILURE;
    }

    ClockTime p1_start = Clock::now();
    auto p1 = part1(argv[1]);
    ClockTime p1_end = Clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(p1_end - p1_start);
    cout << "Part 1: " << p1 << endl;
    cout << "took " << duration1.count() << " ms" << endl;

    ClockTime p2_start = Clock::now();
    auto p2 = part2(argv[1]);
    ClockTime p2_end = Clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(p2_end - p2_start);
    cout << "Part 2: " << p2 << std::endl;
    cout << "took " << duration2.count() << " ms" << endl;
}