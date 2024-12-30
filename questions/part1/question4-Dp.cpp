#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

// Constants for maximum number of items and time limit
const int MAXIMUM_ITEMS_NUMBER = 40;
const int MAX_TIME_AMOUNT = 1100;

// Variables for time limit, weight factor, and number of items
int totalTime, weightFactor, numItems;

int depths[MAXIMUM_ITEMS_NUMBER], values[MAXIMUM_ITEMS_NUMBER];

int dpTable[MAXIMUM_ITEMS_NUMBER][MAX_TIME_AMOUNT];

int decisionPath[MAXIMUM_ITEMS_NUMBER][MAX_TIME_AMOUNT];

vector<int> selectedItems;

// Function to calculate the maximum value that can be obtained
int calculateMaximumValue(int index, int airUsed)
{

    // Base case: no more items
    if (index >= numItems)
        return 0;

    int &currentResult = dpTable[index][airUsed];
    // Return cached result if available
    if (currentResult != -1)
        return currentResult;

    int includeThisItem = 0, excludeThisItem = 0;

    // Check if including the current item is possible
    if (airUsed + (3 * weightFactor * depths[index]) <= totalTime)
        includeThisItem = values[index] + calculateMaximumValue(index + 1, airUsed + (3 * weightFactor * depths[index]));

    // Calculate the value if the current item is excluded
    excludeThisItem = calculateMaximumValue(index + 1, airUsed);

    // Record the decision path based on the better option
    if (includeThisItem > excludeThisItem)
        decisionPath[index][airUsed] = 1;
    else
        decisionPath[index][airUsed] = 2;

    return currentResult = max(includeThisItem, excludeThisItem);
}

// Function to trace the selected items based on the decision path
int followSelectedItems(int index, int airUsed)
{
    // Base case: no more decisions
    if (decisionPath[index][airUsed] == -1)
        return 0;

    if (decisionPath[index][airUsed] == 1)
    {
        // Add the item to the selected list
        selectedItems.push_back(index);
        return 1 + followSelectedItems(index + 1, airUsed + (3 * weightFactor * depths[index]));
    }
    else
    {
        // Skip the current item
        return followSelectedItems(index + 1, airUsed);
    }
}

int main()
{
    // To handle spacing between test cases
    bool isFirstTest = false;

    // Process multiple test cases
    while (cin >> totalTime >> weightFactor)
    {
        if (isFirstTest)
            cout << "\n";
        isFirstTest = true;

        cin >> numItems;
        for (int i = 0; i < numItems; i++)
        {
            cin >> depths[i] >> values[i];
        }

        // Initialize the DP table and decision path with -1
        memset(dpTable, -1, sizeof(dpTable));
        memset(decisionPath, -1, sizeof(decisionPath));

        // Calculate the maximum value
        int maximumProfit = calculateMaximumValue(0, 0);

        // Output the results
        cout << maximumProfit << "\n";
        cout << followSelectedItems(0, 0) << "\n";

        for (int i = 0; i < selectedItems.size(); i++)
        {
            cout << depths[selectedItems[i]] << " " << values[selectedItems[i]] << "\n";
        }
        // Clear the selected items for the next test case
        selectedItems.clear();
    }

    return 0;
}
