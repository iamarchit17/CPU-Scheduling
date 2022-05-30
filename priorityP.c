/*
In Priority Scheduling, every process has a priority (a non-negative integer, generally lower number has higher priority)
the short term scheduler decides on the basis of priority which process to be assigned CPU next 

The following code is a simulation of the Preemptive Priority Scheduling

The matrix mat stores all the data of the processes in the following code
    At index 0 -> Process ID
    At index 1 -> Arrival Time
    At index 2 -> Burst Time
    At index 3 -> Priority (the lower the number, the higher the priority)
    At index 4 -> finish or completion time
    At index 5 -> turn around time
    At index 6 -> waiting time

*/

#include<stdio.h>
#include<limits.h>

void arrangeArrival(int num, int mat[][7]);
void completionTime(int num, int mat[][7]);
void turnAroundTime(int num, int mat[][7]);
void waitingTime(int num, int mat[][7]);
double avgTAT(int num, int mat[][7]);
double avgWT(int num, int mat[][7]);
void priorityScheduling(int num, int mat[][7]);
void printResult(int num, int mat[][7]);

//arranging the processes according to their arrival times
void arrangeArrival(int num, int mat[][7]){
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 4; k++) {
                    
                    int temp = mat[j][k];
                    mat[j][k] = mat[j + 1][k];
                    mat[j + 1][k] = temp;
                }
            }
        }
    }
}

void completionTime(int num, int mat[][7]){
    int ready[num];
    //ready array stores which processes are in the ready queue
    //ready[i] = 0 means process i is not yet arrived
    //ready[i] = 1 means process i is arrived and is in ready queue
    //ready[i] = -1 means process i is terminated

    int rem[num];
    //rem array stores remaining time for all the processes

    for(int i = 0; i < num; i++) ready[i] = 0;
    for(int i = 0; i < num; i++) rem[i] = mat[i][2];
    int j = 0;
    int currTime = mat[0][1];
    int completed = 0;

    while(completed != num){
        
        //processes arriving at or before currTime must be in ready queue
        while(j < num && ready[j] != -1 && mat[j][1] <= currTime){
            ready[j] = 1;
            j++;
        }

        //finding the process with maximum priority
        int maxPriorAmongArrived = INT_MAX;
        for(int k = 0; k < num; k++){
            if(ready[k] == 1 && mat[k][3] < mat[maxPriorAmongArrived][3]){
                maxPriorAmongArrived = k;
            }
        }

        /*if the (arrival time of next process - currTime) is greater than or equal to
          remaining time of maxPrior process, then the maxPrior process should terminate

          else, the maxPrior process may or may not pre-empt
        */
        if((j >= num) || (j <  num && mat[j][1] - currTime >= rem[maxPriorAmongArrived])){
            currTime += rem[maxPriorAmongArrived];
            rem[maxPriorAmongArrived] = -1;
            completed++;
            mat[maxPriorAmongArrived][4] = currTime;
            ready[maxPriorAmongArrived] = -1;
        } else if(j < num && mat[j][1] - currTime < rem[maxPriorAmongArrived]){
            rem[maxPriorAmongArrived] = rem[maxPriorAmongArrived] - (mat[j][1] - currTime);
            currTime = mat[j][1];
        } 

        //if there are no processes and CPU gets idle, the currTime should be equal to arrival time of next process
        if(j < num && j - completed < 1 && mat[j][1] > currTime){
            currTime = mat[j][1];
        }
    }

    turnAroundTime(num, mat);
    waitingTime(num, mat);
    printResult(num, mat);
}

void turnAroundTime(int num, int mat[][7]){
    for(int i = 0; i < num; i++) mat[i][5] = mat[i][4] - mat[i][1];
}

void waitingTime(int num, int mat[][7]){
    for(int i = 0; i < num; i++) mat[i][6] = mat[i][5] - mat[i][2];
}

double avgTAT(int num, int mat[][7]){
    int sum = 0;
    for(int i = 0; i < num; i++) sum += mat[i][5];
    return (double)sum/num;
}

double avgWT(int num, int mat[][7]){
    int sum = 0;
    for(int i = 0; i < num; i++) sum += mat[i][6];
    return (double)sum/num;
}

void priorityScheduling(int num, int mat[][7]){
    arrangeArrival(num, mat);
    completionTime(num, mat);
}

void printResult(int num, int mat[][7]){
    printf("\t\t\t\t\tPreemptive Priority Scheduling\n");
    printf("Process ID \t Arrival Time \t Burst Time \t Priority \t Completion Time \t Turn Around Time \t Waiting Time\n");
    for(int i = 0; i < num; i++){
        printf("    %d\t\t\t%d\t     %d\t\t    %d    \t\t%d\t\t\t%d\t\t     %d\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3], mat[i][4], mat[i][5], mat[i][6]);
    }

    printf("Average Turn Around Time : %f\n", avgTAT(num, mat));
    printf("Average Wait Time : %f\n", avgWT(num, mat));
}

int main(){
    int n;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    int mat[n][7];

    printf("Enter 0 to put custom process ID's or -1 to give default 1 to N as process ID's : ");
    int id;
    scanf("%d", &id);

    if(id == -1){
        for(int i = 0; i < n; i++) mat[i][0] = i + 1;
    } else {
        printf("Enter Process ID's(separated by spaces) : ");
        for(int i = 0; i < n; i++){
            int s;
            scanf("%d", &s);
            mat[i][0] = s;
        }
    }

    printf("Enter Arrival Times(separated by spaces) : ");

    for(int i = 0; i < n; i++){
        int s;
        scanf("%d", &s);
        mat[i][1] = s;
    }

    printf("Enter Burst Times(separated by spaces) : ");

    for(int i = 0; i < n; i++){
        int s;
        scanf("%d", &s);
        mat[i][2] = s;
    }

    printf("Enter Priorities(separated by spaces) : ");

    for(int i = 0; i < n; i++){
        int s;
        scanf("%d", &s);
        mat[i][3] = s;
    }
    
    priorityScheduling(n, mat);
}