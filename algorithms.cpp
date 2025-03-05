#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct job{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
};

void FCFS(vector<job> &jobs) {
    // Sort jobs by arrival time
    sort(jobs.begin(), jobs.end(), [](job a, job b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int time = 0;
    cout << "FCFS Scheduling Order:" << endl;

    for (auto &job : jobs) {
        // Handle idle time (if the CPU is idle when the job arrives)
        if (time < job.arrivalTime) {
            time = job.arrivalTime;
        }

        // Calculate waiting time and turnaround time
        int waitingTime = time - job.arrivalTime; // Corrected waiting time calculation
        int turnaroundTime = waitingTime + job.burstTime;

        // Output job details
        cout << "Job " << job.id << " starts at time " << time 
             << ", finishes at time " << time + job.burstTime 
             << ", Waiting Time: " << waitingTime 
             << ", Turnaround Time: " << turnaroundTime << endl;

        // Update the time after the job finishes
        time += job.burstTime;
    }
}



