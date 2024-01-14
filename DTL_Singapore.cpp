// Design and implement a job scheduler

#include <functional>
#include <bits/stdc++.h>

struct task
{
    using Callback = std::function<void()>;
    Callback callback;
    int64_t start = -1;
    int64_t interval = -1;
    int64_t end = -1;
    int64_t last_time = -1;
};

class Scheduler
{

    using Callback = std::function<void()>;
    int64_t time = 0;
    vector<struct task> tasks;

    void UpdateTime(int64_t microseconds);
    void Schedule(int64_t start, Callback callback);
    void Schedule(int64_t start, int64_t interval, int64_t end, Callback callback);
    bool execute(int64_t current_time, int64_t start, int64_t interval, int64_t end, int64_t last_time, Callback callback);
};

/*
Example:

Schedule(20, 20, 200, f) // at moments 20-40-60-80-..., call f()
UpdateTime(10)  // current time is 10
UpdateTime(30)  // current time is 30, moment 20 has passed, so need to call f()
Schedule(50, g)  // at moment 50, call g()
UpdateTime(100) // current time is 100, call f()-g()-f()-f()-f()
*/

// Check if the required condition to execute callback are satisfied
bool Scheduler::execute(int64_t current_time, int64_t start, int64_t interval, int64_t end, int64_t last_time, Callback callback)
{

    int64_t diff;
    int64_t n;
    int64_t last_exec_time;

    // Find difference between current and start time
    diff = (current_time - start);
    if (end == -1)
    {
        callback();
        return;
    }

    // Reaching here implies the task is of a periodic kind

    n = diff / interval;
    last_time = start + n * interval;

    // Get to last required execution time before end time
    while (last_exec_time > end)
    {
        last_exec_time -= interval;
    }

    // Check if the last time the callback needs to be called lies after last_time
    while (last_time <= last_exec_time)
    {
        callback();
        last_exec_time -= interval;
    }

    // Check if current time is below the end time
    if (end != -1 && current_time > end)
        diff = 1;

    if(diff == 0)
        return true;

    return false;        
}

void Scheduler::UpdateTime(int64_t microseconds)
{

    int64_t size = tasks.size();

    for (int i = 0; i < size; i++)
    {

        if (microseconds < tasks[i].start)
            continue;

        // Execute callbacks when required
        Scheduler::execute(microseconds, tasks[i].start, tasks[i].interval, tasks[i].end, tasks[i].last_time, tasks[i].callback());
      
        if(tasks[i].end == -1 || microseconds > tasks.end)
        tasks.erase(&tasks[i]);

        tasks[i].last_time = microseconds;
    }

    return;
}

// #include <iostream>
// using namespace std;

// int main() {
// 	cout<<"Hello";
// 	return 0;
// }
