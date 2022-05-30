/*
Response Ratio = (burst time + wait Time)/burst Time
The short term scheduler selects the process with highest response ratio and allots the CPU
Non-Premptive means process will pre-empt(will terminate or wait for I/O) request once CPU is allotted to it

The following code is a simulation of the  Non-Preemptive Highest Resoponse Ratio Next Scheduling
The matrix mat stores all the data of the processes in the following code
    At index 0 -> Process ID
    At index 1 -> Arrival Time
    At index 2 -> Burst Time
    At index 3 -> finish or completion time
    At index 4 -> turn around time
    At index 5 -> waiting time

*/

#include<stdio.h>
#include<limits.h>

void arrangeArrival(int num, int mat[][6]);
void completionTime(int num, int mat[][6]);
void turnAroundTime(int num, int mat[][6]);
void waitingTime(int num, int mat[][6]);
double avgTAT(int num, int mat[][6]);
double avgWT(int num, int mat[][6]);
void HRRNScheduling(int num, int mat[][6]);
void printResult(int num, int mat[][6]);

void arrangeArrival(int num, int mat[][6]){
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 3; k++) {
                    
                    int temp = mat[j][k];
                    mat[j][k] = mat[j + 1][k];
                    mat[j + 1][k] = temp;
                }
            }
        }
    }

}

void completionTime(int num, int mat[][6]){
    int ready[num];
    for(int i = 0; i < num; i++) ready[i] = 0;

    //ready array stores which processes are in the ready queue
    //ready[i] = 0 means process i is not yet arrived
    //ready[i] = 1 means process i is arrived and is in ready queue
    //ready[i] = -1 means process i is terminated

    int j = 0;
    int currTime = mat[0][1];
    int completed = 0;

    double hrrn[num];
    //stores response ratio for each process at all times
    for(int i = 0; i < num; i++) hrrn[i] = 0.0;
    //since response ration is always >= 1, response ratio = 0, means
    //process has not yet arrived
    //and response ratio = -1 means process has terminated

    while(completed != num){
        
        //processes arriving at or before currTime must be in ready queue
        while(j < num && ready[j] != -1 && mat[j][1] <= currTime){
            ready[j] = 1;
            j++;
        }

        //calculating response ration for each arrived process
        for(int k = 0; k < num; k++){
            if(ready[k] == 1){
                hrrn[k] = 1.0 + (double)(currTime - mat[k][1])/mat[k][2];
            }
        }

        for(int k = 0; k < num; k++) printf("%f ", hrrn[k]);
        printf("\n");

        int currProc = -1; //process with highest response ratio
        int hrr = INT_MIN; //highest response ratio

        for(int k = 0; k < num; k++){
            if(ready[k] == 1 && hrrn[k] > hrr){
                currProc = k;
                hrr = hrrn[k];
            }
        }

        //assigning CPU time to currProc
        currTime += mat[currProc][2];
        mat[currProc][3] = currTime;
        completed++;
        ready[currProc] = -1;
        hrrn[currProc] = -1.0;
        
        //in case there are no processes and CPU is idle,
        //currTime must be set to arrival time of next process
        if(j < num && j - completed < 1 && mat[j][1] > currTime){
            currTime = mat[j][1];
        }
        
    }
    turnAroundTime(num, mat);
    waitingTime(num, mat);
    printResult(num, mat);
}

void turnAroundTime(int num, int mat[][6]){
    for(int i = 0; i < num; i++) mat[i][4] = mat[i][3] - mat[i][1];
}

void waitingTime(int num, int mat[][6]){
    for(int i = 0; i < num; i++) mat[i][5] = mat[i][4] - mat[i][2];
}

double avgTAT(int num, int mat[][6]){
    int sum = 0;
    for(int i = 0; i < num; i++) sum += mat[i][4];
    return (double)sum/num;
}

double avgWT(int num, int mat[][6]){
    int sum = 0;
    for(int i = 0; i < num; i++) sum += mat[i][5];
    return (double)sum/num;
}

void HRRNScheduling(int num, int mat[][6]){
    arrangeArrival(num, mat);
    completionTime(num, mat);
}

void printResult(int num, int mat[][6]){
    printf("\t\t\tNon-Preemptive Highest Response Ratio Next Scheduling\n");
    printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Turn Around Time \t Waiting Time\n");
    for(int i = 0; i < num; i++){
        printf("    %d\t\t\t%d\t     %d   \t\t%d\t\t\t%d\t\t     %d\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3], mat[i][4], mat[i][5]);
    }

    printf("Average Turn Around Time : %f\n", avgTAT(num, mat));
    printf("Average Wait Time : %f\n", avgWT(num, mat));
}

int main(){
    int n;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    int mat[n][6];

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

    HRRNScheduling(n, mat);
}