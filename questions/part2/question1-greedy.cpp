#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int GreedyAlgorithm(vector<int> &children, vector<int> &cookies)
{
    sort(children.begin(), children.end());
    sort(cookies.begin(), cookies.end());

    int i = 0, j = 0, satisfied = 0;

    while (i < children.size() && j < cookies.size())
    {
        if (cookies[j] >= children[i])
        {
            satisfied++;
            i++;
        }
        j++;
    }

    return satisfied;
}

int main()
{
    vector<int> children1 = {2, 3, 1};
    vector<int> cookies1 = {1, 1};

    cout << "Satisfied children = " << GreedyAlgorithm(children1, cookies1) << endl;

    vector<int> children2 = {1, 2, 4};
    vector<int> cookies2 = {1, 2, 3};

    cout << "Satisfied children = " << GreedyAlgorithm(children2, cookies2) << endl;

    return 0;
}