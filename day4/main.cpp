#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <openssl/evp.h>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

// stolen from https://stackoverflow.com/a/73843621 since I didn't
// feel like figuring this out
string md5(const string &content)
{
    EVP_MD_CTX *context = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    string output;

    EVP_DigestInit_ex2(context, md, NULL);
    EVP_DigestUpdate(context, content.c_str(), content.length());
    EVP_DigestFinal_ex(context, md_value, &md_len);
    EVP_MD_CTX_free(context);

    output.resize(md_len * 2);
    for (unsigned int i = 0; i < md_len; ++i)
        std::sprintf(&output[i * 2], "%02x", md_value[i]);
    return output;
}

int part1(char *input)
{
    int i = 1;
    while (true)
    {
        stringstream ss;
        ss << input;
        ss << i;
        string out = md5(ss.str());
        if (out.rfind("00000", 0) == 0)
        {
            return i;
        }
        i += 1;
    }
}

int part2(char *input)
{
    int i = 1;
    while (true)
    {
        stringstream ss;
        ss << input;
        ss << i;
        string out = md5(ss.str());
        if (out.rfind("000000", 0) == 0)
        {
            return i;
        }
        i += 1;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "usage: " << argv[0] << " [string]" << endl;
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