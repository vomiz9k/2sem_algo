#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using std::vector;
using std::string;



const unsigned long long p = 2017, m1 = ~0;
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
    int n, m;
    std::cin >> n >> m;

    vector<int> vec(n);
    for (int i = 0; i < n; ++i)
        std::cin >> vec[i];

    vector<unsigned long long> hashes(n + 1);
    vector<unsigned long long> back_hashes(n + 1);

    unsigned long long result = 0;
    for (int i = 1; i <= n; ++i)
    {
        result = (p * result + vec[i - 1]) % m1;
        hashes[i] = result;
    }
    result = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        result = (p * result + vec[i]) % m1;
        back_hashes[i] = result;
    }

    vector<unsigned long long> p_degrees(n + 1);
    p_degrees[0] = 1;
    for (int i = 1; i <= n; ++i)
        p_degrees[i] = (p_degrees[i - 1] * p) % m1;

    vector<int> answers;

    for (int i = 0; i < n / 2; ++i)
    {
        if (hashes[i + 1] == (back_hashes[i + 1] - back_hashes[2 * i + 2] * p_degrees[i + 1]) % m1)
        {
            bool same = true;
            for(int j = 0; j < i + 1; ++j)
                if (vec[j] != vec[2 * i + 1 - j])
                {
                    same = false;
                    break;
                }
            if (same)
                answers.push_back(n - i - 1);
        }
    }

    for (int i = 0; i < answers.size(); ++i)
        std::cout << answers[answers.size() - 1 - i] << ' ';
    std::cout << n;
}

--