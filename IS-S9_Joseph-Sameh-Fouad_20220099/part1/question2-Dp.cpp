/*
 * author: 	Joseph Sameh 20220099
 */

#include <bits/stdc++.h>

using namespace std;

long long fib[100000 + 5];
long long mod = 1e9 + 7;

long long containWM(string s)
{
    for (char c : s)
    {
        if (c == 'w' || c == 'm')
        {
            return 1;
        }
    }
    return 0;
}

void checkForCharOccurrence(const string &s, const char &ch, long long &sum)
{
    long long answer = 0;
    for (char c : s)
    {
        if (c == ch)
        {
            answer++;
        }
        else if (answer > 0)
        {
            sum = (sum * fib[answer]) % mod;
            answer = 0;
        }
    }
    if (answer > 0)
    {
        sum = (sum * fib[answer]) % mod;
        answer = 0;
    }
}

int main()
{
    string s;
    cin >> s;

    int n = s.size();

    fib[1] = 1;
    fib[2] = 2;

    for (int i = 3; i <= n; i++)
    {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    }

    if (containWM(s))
    {
        cout << "0";
    }

    else
    {
        long long sum = 1;

        checkForCharOccurrence(s, 'n', sum);

        checkForCharOccurrence(s, 'u', sum);

        cout << sum;
    }
    return 0;
}