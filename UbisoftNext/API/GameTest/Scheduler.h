#pragma once
#include <list>
#include <chrono>
#include <functional>

using timePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

/// <summary>
/// task object that
/// </summary>
class Task {
private:
    timePoint m_StartTime;
    timePoint m_EndTime;
    std::function<void()> m_Task;
public:
    Task(
        std::function<void()> task,
        timePoint startTime,
        timePoint endTime
    ) :
        m_Task(std::move(task)),
        m_StartTime(startTime),
        m_EndTime(endTime) {}

    void Execute() {
        m_Task();
    }

    bool IsReady() {
        return std::chrono::high_resolution_clock::now() >= m_StartTime;
    }
};

class Scheduler {
private:
    std::list<Task> m_Tasks;
public:

    void AddTask(Task task) {
        m_Tasks.push_back(task);
    }
    //adds task with delay in miliiseconds
    void AddTask(std::function<void()> task,int delay)
    {
        m_Tasks.push_back(
            Task(task, std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(delay), std::chrono::high_resolution_clock::now() )

        );
    }
    void Update() {
        for (auto it = m_Tasks.begin(); it != m_Tasks.end(); ) {
            if (it->IsReady()) {
                it->Execute();
                it = m_Tasks.erase(it);
            }
            else {
                ++it;
            }
        }
    }
};
