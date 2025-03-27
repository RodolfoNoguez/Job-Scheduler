#include "algorithms.hpp"


using namespace std;


int main(){
    
    vector<Job> jobs = {
        {1, 0, 5, 3},
        {2, 2, 3, 1},
        {3, 3, 8, 4},
        {4, 5, 6, 2},
        {5, 6, 4, 5}
    };

    scheduleJobs(jobs);
    return 0;
}