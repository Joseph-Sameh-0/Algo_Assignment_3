/*
 * author: 	Miguel Reda 20220352
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to find the length of the longest increasing subsequence
int longestIncreasingSubsequence(vector<int> &A)
{
    int N = A.size();
    // Initialize dp array where dp[i] represents the length of the longest increasing subsequence ending at index i
    vector<int> dp(N, 1);

    // Iterate through the array to fill the dp array
    for (int i = 1; i < N; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            // If A[i] is greater than A[j], then A[i] can be appended to the increasing subsequence ending at A[j]
            if (A[i] > A[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    // The length of the longest increasing subsequence will be the maximum value in the dp array
    return *max_element(dp.begin(), dp.end());
}

int main()
{
    int N;
    // Read the size of the array
    cin >> N;
    vector<int> A(N);
    // Read the elements of the array
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    // Output the length of the longest increasing subsequence
    cout << longestIncreasingSubsequence(A) << endl;

    return 0;
}
