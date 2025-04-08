#include <iostream>
#include <algorithm>
#include "algorithms.hpp"


void FCFS(vector<Job> &jobs) {
    // Sort jobs by arrival time
    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
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
        int waitingTime = time - job.arrivalTime; 
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


void SJN(vector<Job> &jobs) {
    // Sort jobs by arrival time (and burst time if arrival times are equal)
    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) {
        return (a.arrivalTime < b.arrivalTime) || 
               (a.arrivalTime == b.arrivalTime && a.burstTime < b.burstTime);
    });

    // Min-heap to prioritize jobs with the shortest burst time
    auto compareBurstTime = [](const Job &a, const Job &b) {
        return a.burstTime > b.burstTime;
    };
    priority_queue<Job, vector<Job>, decltype(compareBurstTime)> minHeap(compareBurstTime);

    int currentTime = 0;
    size_t completedJobs = 0;
    size_t index = 0;

    cout << "SJN Scheduling Order:\n";

    while (completedJobs < jobs.size()) {
        // Push all jobs that have arrived by the current time into the min-heap
        while (index < jobs.size() && jobs[index].arrivalTime <= currentTime) {
            minHeap.push(jobs[index]);
            index++;
        }

        if (!minHeap.empty()) {
            // Execute the shortest job available
            Job shortestJob = minHeap.top();
            minHeap.pop();
            currentTime += shortestJob.burstTime;
            completedJobs++;
            cout << "Job " << shortestJob.id << " (Arrival: " << shortestJob.arrivalTime 
                 << ", Burst: " << shortestJob.burstTime << ") executed at time " 
                 << currentTime << "\n";
        } else {
            // If no job is available, move to the next job arrival time
            if (index < jobs.size()) {
                currentTime = jobs[index].arrivalTime;
            }        }
    }
}

void PriorityScheduling(vector<Job> &jobs) {
    // Sort jobs by arrival time
    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Min-Heap for priority queue (lower priority value means higher priority)
    auto comparePriority = [](const Job &a, const Job &b) {
        return a.priority > b.priority; // Lower priority value comes first
    };
    priority_queue<Job, vector<Job>, decltype(comparePriority)> priorityQueue(comparePriority);

    int currentTime = 0;
    size_t completedJobs = 0;
    size_t index = 0;

    cout << "Priority Scheduling Order:\n";

    while (completedJobs < jobs.size()) {
        // Add all jobs that have arrived to the priority queue
        while (index < jobs.size() && jobs[index].arrivalTime <= currentTime) {
            priorityQueue.push(jobs[index]);
            index++;
        }

        if (!priorityQueue.empty()) {
            Job currentJob = priorityQueue.top();
            priorityQueue.pop();
            currentTime += currentJob.burstTime;
            completedJobs++;

            cout << "Job " << currentJob.id 
                 << " (Priority: " << currentJob.priority 
                 << ", Arrival: " << currentJob.arrivalTime 
                 << ", Burst: " << currentJob.burstTime 
                 << ") executed at time " << currentTime << "\n";
        } else {
            // Jump to the next job’s arrival time if no job is available
            if (index < jobs.size()) {
                currentTime = jobs[index].arrivalTime;
            }
        }
    }
}


void RoundRobin(vector<Job> &jobs, int quantum) {
    if (quantum <= 0) {
        cout << "Error: Quantum must be a positive value.\n";
        return;
    }

    queue<Job> readyQueue;
    int currentTime = 0;
    size_t index = 0;

    cout << "Round Robin Scheduling Order (Quantum: " << quantum << "):\n";

    while (!readyQueue.empty() || index < jobs.size()) {
        // Add jobs to the queue that have arrived by the current time
        while (index < jobs.size() && jobs[index].arrivalTime <= currentTime) {
            readyQueue.push(jobs[index]);
            index++;
        }

        if (readyQueue.empty()) {
            // If no job is available, fast-forward to the next job's arrival time
            currentTime = jobs[index].arrivalTime;
            continue;
        }

        Job currentJob = readyQueue.front();
        readyQueue.pop();

        // Execute the job for the minimum of its remaining burst time and the quantum
        int executionTime = min(currentJob.burstTime, quantum);
        currentTime += executionTime;
        currentJob.burstTime -= executionTime;

        cout << "Job " << currentJob.id << " executed for " << executionTime 
             << " units. Remaining burst time: " << currentJob.burstTime 
             << " at time " << currentTime << "\n";

        if (currentJob.burstTime > 0) {
            // Re-queue the job if it still has remaining burst time
            readyQueue.push(currentJob);
        } else {
            // Job is completed
            cout << "Job " << currentJob.id << " finished at time " << currentTime << "\n";
        }
    }
}



void scheduleJobs(vector<Job> &jobs) {
    // Display available scheduling algorithms
    int choice;
    cout << "Select a scheduling algorithm:\n";
    cout << "1. First-Come, First-Served (FCFS)\n";
    cout << "2. Shortest Job Next (SJN)\n";
    cout << "3. Priority Scheduling\n";
    cout << "4. Round Robin\n";
    cout << "Enter your choice: ";
    cin >> choice;
    // Call the selected scheduling algorithm
    if (choice == 1){
        FCFS(jobs);
    }
    else if (choice == 2){
        SJN(jobs);
    }
    else if (choice == 3){
        PriorityScheduling(jobs);
    }
    else if (choice == 4){
        int quantum;
        cout << "Enter the time quantum for Round Robin: ";
        cin >> quantum;
        RoundRobin(jobs, quantum);
    }
    else{
        cout << "Invalid choice. Please try again.\n";
    }
}   
