#include "algorithms.hpp"


using namespace std;


int main(){
    // A placeholder vector witha list of jobs for execution 
    vector<Job> jobs = {
        {1, 0, 5, 3},
        {2, 2, 3, 1},
        {3, 3, 8, 4},
        {4, 5, 6, 2},
        {5, 6, 4, 5}
    };
    // this will call the scheduleJobs function to start the scheduling process 
    scheduleJobs(jobs);
    return 0;
}

//please read read the readme.md file for instructions on how to run the code 