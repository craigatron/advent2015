#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

struct pair_hash
{
    inline size_t operator()(const pair<int, int> &v) const
    {
        return v.first * 31 + v.second;
    }
};

int part1(char *file)
{
    ifstream input_file(file);
    if (!input_file)
    {
        throw invalid_argument("invalid file");
    }
    string line;
    getline(input_file, line);

    unordered_set<pair<int, int>, pair_hash> coords;

    coords.insert(pair(0, 0));

    auto current_x = 0;
    auto current_y = 0;

    for (char &ch : line)
    {
        switch (ch)
        {
        case '^':
            current_y += 1;
            break;
        case '>':
            current_x += 1;
            break;
        case '<':
            current_x -= 1;
            break;
        case 'v':
            current_y -= 1;
            break;
        default:
            throw invalid_argument("invalid char");
        }
        coords.insert(pair(current_x, current_y));
    }

    return coords.size();
}

int part2(char *file)
{
    ifstream input_file(file);
    if (!input_file)
    {
        throw invalid_argument("invalid file");
    }
    string line;
    getline(input_file, line);

    unordered_set<pair<int, int>, pair_hash> coords;

    coords.insert(pair(0, 0));

    int santa_x = 0;
    int santa_y = 0;
    int robo_x = 0;
    int robo_y = 0;

    for (int i = 0; i < line.length(); i++)
    {
        int *inc_x = i % 2 == 0 ? &santa_x : &robo_x;
        int *inc_y = i % 2 == 0 ? &santa_y : &robo_y;
        switch (line[i])
        {
        case '^':
            *inc_y += 1;
            break;
        case '>':
            *inc_x += 1;
            break;
        case '<':
            *inc_x -= 1;
            break;
        case 'v':
            *inc_y -= 1;
            break;
        default:
            throw invalid_argument("invalid char");
        }
        coords.insert(pair(*inc_x, *inc_y));
    }

    return coords.size();
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
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(p1_end - p1_start);
    cout << "Part 2: " << p2 << std::endl;
    cout << "took " << duration2.count() << " ms" << endl;
}