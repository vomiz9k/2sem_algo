#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using std::vector;
using std::string;



const unsigned long long p = 2017;
unsigned long long hash(const string& str, vector<unsigned long long>& hashes)
{
    unsigned long long result = 0;
    for (int i = 1; i <= str.length(); ++i)
    {
        result = p * result + str[i - 1];
        hashes[i] = result;
    }
    return result;
}
unsigned long long hash(const string& str)
{
    unsigned long long result = 0;
    for (int i = 0; i < str.length(); ++i)
        result = p * result + str[i];

    return result;
}



int main()
{
    string S, T;
    std::cin >> S >> T;
    vector<unsigned long long> hashes(S.length() + 1);
    hash(S, hashes);
    unsigned long long T_hash = hash(T);

    unsigned long long deg_p = 1;
    for (int i = 0; i < T.length(); ++i)
        deg_p *= p;

    for (int i = 0; i <= S.length() - T.length(); ++i)
    {
        if (hashes[i + T.length()] - hashes[i] * deg_p == T_hash && memcmp(T.c_str(), S.c_str() + i, T.length()) == 0)
            std::cout << i << ' ';
    }
}

