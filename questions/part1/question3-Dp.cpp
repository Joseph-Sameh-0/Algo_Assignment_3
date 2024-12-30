#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int K, M;
        cin >> K >> M;
        vector<int> weights(M), values(M);
        for (int i = 0; i < M; ++i)
        {
            cin >> weights[i] >> values[i];
        }

        vector<int> dp(K + 1, 0); // Initialize dp array with 0s for weights from 0 to K
        for (int i = 0; i < M; ++i)
        {
            for (int w = K; w >= weights[i]; --w)
            {
                // Update dp[w] to the maximum of its current value or the value of including the current item
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]); // Calculate the best value for weight w
            }
        }

        cout << "Hey stupid robber, you can get " << dp[K] << "." << endl;
    }
    return 0;
}
