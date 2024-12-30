/*
 * author: 	Joseph Sameh 20220099
 */

#include <bits/stdc++.h>
using namespace std;

struct Task
{
    char name;
    long long freq;

    Task(char n, long long f) : name(n), freq(f) {};
    bool operator<(const Task &other) const { return freq < other.freq; }
    bool operator>(const Task &other) const { return freq > other.freq; };
    bool operator>=(const Task &other) const { return freq >= other.freq; };
};

int leastInterval(vector<char> &tasks, int n)
{
    if (tasks.empty())
        return 0;

    map<char, int> m;
    priority_queue<Task> q;
    long long time = 0;

    for (char task : tasks)
    {
        m[task]++;
    }

    for (auto &it : m)
    {
        Task t(it.first, it.second);
        q.push(t);
    }

    char maxFreq = q.top().name;

    while (!q.empty())
    {
        long long cycle = n + 1;
        // cout << "q.size() = " << q.size() << endl;
        // cout << "time = " << time << endl;
        // cout << "maxFreq = " << maxFreq << endl;
        // cout << "n = " << n << endl;

        queue<Task> store;

        while (!q.empty() && cycle)
        {
            // cout << "iteration = " << iteration << endl;
            Task t(q.top().name, q.top().freq - 1);
            // cout << t.name << " ";

            q.pop();
            if (t.freq > 0)
            {
                store.push(t);
            }
            cycle--;
            time++;
        }

        while (!store.empty())
        {
            q.push(store.front());
            store.pop();
        }

        if (!q.empty())
        {
            // for (size_t i = 0; i < cycle; i++)
            // {
            //     cout << "idel ";
            // }
            time += cycle;
        }
    }
    // cout << endl;

    // print the queue
    // while (!q.empty())
    // {
    //     cout << q.top().name << " " << q.top().freq << endl;
    //     q.pop();
    // }

    return time;
}

int main()
{
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    long long n = 2;
    cout << leastInterval(tasks, n) << endl;

    tasks = {'A', 'C', 'A', 'B', 'D', 'B'};
    n = 1;
    cout << leastInterval(tasks, n) << endl;

    tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    n = 3;
    cout << leastInterval(tasks, n) << endl;

    return 0;
}