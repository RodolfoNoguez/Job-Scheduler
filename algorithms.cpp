#include <iostream>
#include <algorithm>
#include "algorithms.hpp"


void FCFS(vector<Job> &jobs) {
    // This sorts the jobs by arrival time
    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int time = 0;
    cout << "First Come First Serve Scheduling Order:" << endl;

    for (auto &job : jobs) {
        // This handles the idle time between jobs
        if (time < job.arrivalTime) {
            time = job.arrivalTime;
        }

        // This calculates the waiting time and turnaround time
        int waitingTime = time - job.arrivalTime; 
        int turnaroundTime = waitingTime + job.burstTime;

        // This prints the job details 
        cout << "Job " << job.id << " starts at time " << time  << ", finishes at time " << time + job.burstTime << ", Waiting Time: " << waitingTime << ", Turnaround Time: " << turnaroundTime << endl;

        // This updates the current time after the job is completed
        time += job.burstTime;
    }
}


void SJN(vector<Job> &jobs) {
    // This sorts the jobs by arrival time and burst time if arrival times are equal
    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) {
        return (a.arrivalTime < b.arrivalTime) || 
               (a.arrivalTime == b.arrivalTime && a.burstTime < b.burstTime);
    });

    // This is a Min-heap that prioritize jobs with the shortest burst time
    auto compareBurstTime = [](const Job &a, const Job &b) {
        return a.burstTime > b.burstTime;
    };
    priority_queue<Job, vector<Job>, decltype(compareBurstTime)> minHeap(compareBurstTime);

    int time = 0;
    size_t finishedJobs = 0;
    size_t index = 0;

    cout << "Shortest Job Next Scheduling Order:\n";

    while (finishedJobs < jobs.size()) {
        // This Pushes all jobs that have arrived by the current time into the min-heap
        while (index < jobs.size() && jobs[index].arrivalTime <= time) {
            minHeap.push(jobs[index]);
            index++;
        }

        if (!minHeap.empty()) {
            // This will handle and execute the shortest job available
            Job shortestJob = minHeap.top();
            minHeap.pop();
            time += shortestJob.burstTime;
            finishedJobs++;
            cout << "Job: " << shortestJob.id << " Arrival: " << shortestJob.arrivalTime << ", Burst: " << shortestJob.burstTime << " executed at time: " << time << "\n";
        } else {
            // If there is no job is available it will move to the next job 
            if (index < jobs.size()) {
                time = jobs[index].arrivalTime;
            }        
        }
    }
}

void PriorityScheduling(vector<Job> &jobs) {
    // This will sort jobs by arrival time
    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // This is a Min-Heap for priority queue a lower priority value means higher priority which means that it will go first
    auto comparePriority = [](const Job &a, const Job &b) {
        return a.priority > b.priority; 
    };
    priority_queue<Job, vector<Job>, decltype(comparePriority)> priorityQueue(comparePriority);

    int time = 0;
    size_t finishedJobs = 0;
    size_t index = 0;

    cout << "Priority Scheduling Order:\n";

    while (finishedJobs < jobs.size()) {
        // This will add all the jobs that have arrived to the priority queue
        while (index < jobs.size() && jobs[index].arrivalTime <= time) {
            priorityQueue.push(jobs[index]);
            index++;
        }

        if (!priorityQueue.empty()) {
            Job currentJob = priorityQueue.top();
            priorityQueue.pop();
            time += currentJob.burstTime;
            finishedJobs++;

            cout << "Job: " << currentJob.id << " Priority: " << currentJob.priority << ", Arrival: " << currentJob.arrivalTime << ", Burst: " << currentJob.burstTime << " executed at time: " << time << "\n";
        } else {
            // This will jump to the next job if no job is available
            if (index < jobs.size()) {
                time = jobs[index].arrivalTime;
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
    int time = 0;
    size_t index = 0;

    cout << "Round Robin Scheduling Order, Quantum: " << quantum << ":\n";

    while (!readyQueue.empty() || index < jobs.size()) {
        // This will add jobs to the queue that have arrived by the current time
        while (index < jobs.size() && jobs[index].arrivalTime <= time) {
            readyQueue.push(jobs[index]);
            index++;
        }

        if (readyQueue.empty()) {
            // If there is no job available. it will move forwatd to the next jobs time.
            time = jobs[index].arrivalTime;
            continue;
        }

        Job currentJob = readyQueue.front();
        readyQueue.pop();

        // This will execute the job for the minimum of its remaining burst time and the quantum
        int executionTime = min(currentJob.burstTime, quantum);
        time += executionTime;
        currentJob.burstTime -= executionTime;

        cout << "Job " << currentJob.id << " executed for " << executionTime << " units. Remaining burst time: " << currentJob.burstTime << " ,at time " << time << "\n";

        if (currentJob.burstTime > 0) {
            // This will requeue the job if it still has remaining burst time
            readyQueue.push(currentJob);
        } else {
            // This is the message receives once the job is completed
            cout << "Job " << currentJob.id << " finished at time " << time << "\n";
        }
    }
}



void scheduleJobs(vector<Job> &jobs) {
    // This displays the available scheduling algorithms
    int choice;
    cout << "Select a scheduling algorithm:\n";
    cout << "1. First Come First Serve\n";
    cout << "2. Shortest Job Next\n";
    cout << "3. Priority Scheduling\n";
    cout << "4. Round Robin\n";
    cout << "Please enter your choice: ";
    cin >> choice;
    // This will call the selected scheduling algorithm
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
        cout << "Please enter the time quantum for Round Robin: ";
        cin >> quantum;
        RoundRobin(jobs, quantum);
    }
    else{
        cout << "Invalid choice. Please try again and enter a correct choice.\n";
    }
}   
