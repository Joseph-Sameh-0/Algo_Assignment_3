/*
 * author: 	Youssef Joseph 20220389
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int minimalDifference(vector<int> &coins)
{
    int totalSum = accumulate(coins.begin(), coins.end(), 0);
    int halfSum = totalSum / 2;
    vector<bool> dp(halfSum + 1, false);
    dp[0] = true;

    for (int coin : coins)
    {
        for (int j = halfSum; j >= coin; --j)
        {
            dp[j] = dp[j] || dp[j - coin];
        }
    }

    for (int s1 = halfSum; s1 >= 0; --s1)
    {
        if (dp[s1])
        {
            int s2 = totalSum - s1;
            return abs(s2 - s1);
        }
    }
    return totalSum;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int m;
        cin >> m;
        vector<int> coins(m);
        for (int i = 0; i < m; ++i)
        {
            cin >> coins[i];
        }
        cout << minimalDifference(coins) << endl;
    }
    return 0;
}