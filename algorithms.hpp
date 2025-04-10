// scheduling_algorithms.h
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <queue>
using namespace std;

// This is the Job structure that holds the job details for the algorithms
struct Job {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
};
// These are the function prototypes for the scheduling algorithms
void FCFS(vector<Job> &jobs);
void SJN(vector<Job> &jobs);
void PriorityScheduling(vector<Job> &jobs);
void RoundRobin(vector<Job> &jobs, int quantum);
void scheduleJobs(vector<Job> &jobs);

#endif