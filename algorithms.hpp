// scheduling_algorithms.h
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <queue>
using namespace std;

// Job structure to hold job details
struct Job {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
};
// Function prototypes for scheduling algorithms
void FCFS(vector<Job> &jobs);
void SJN(vector<Job> &jobs);
void PriorityScheduling(vector<Job> &jobs);
void RoundRobin(vector<Job> &jobs, int quantum);
void scheduleJobs(vector<Job> &jobs);

#endif