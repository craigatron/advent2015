#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

bool is_nice_p1(string s)
{
    int vowel_count = 0;
    bool contains_double = false;
    char last_char = ' ';
    for (char &c : s)
    {
        if (c == 'b' && last_char == 'a' || c == 'd' && last_char == 'c' || c == 'q' && last_char == 'p' || c == 'y' && last_char == 'x')
        {
            return false;
        }
        if (c == last_char)
        {
            contains_double = true;
        }
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            vowel_count++;
        }
        last_char = c;
    }
    return vowel_count >= 3 && contains_double;
}

int part1(char *file)
{
    ifstream input_file(file);
    if (!input_file)
    {
        throw std::invalid_argument("invalid file");
    }
    string line;
    int nice = 0;
    while (getline(input_file, line))
    {
        if (is_nice_p1(line))
        {
            nice++;
        }
    }

    return nice;
}

bool is_nice_p2(string s)
{
    bool has_double_pair = false;
    for (int i = 0; i < s.length() - 3; i++)
    {
        char c1 = s.at(i);
        char c2 = s.at(i + 1);
        for (int j = i + 2; j < s.length() - 1; j++)
        {
            if (c1 == s.at(j) && c2 == s.at(j + 1))
            {
                has_double_pair = true;
                i = s.length();
                j = s.length();
            }
        }
    }
    if (!has_double_pair)
    {
        return false;
    }

    for (int i = 1; i < s.length() - 1; i++)
    {
        if (s.at(i - 1) == s.at(i + 1))
        {
            return true;
        }
    }
    return false;
}

int part2(char *file)
{
    ifstream input_file(file);
    if (!input_file)
    {
        throw std::invalid_argument("invalid file");
    }
    string line;
    int nice = 0;
    while (getline(input_file, line))
    {
        if (is_nice_p2(line))
        {
            nice++;
        }
    }

    return nice;
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