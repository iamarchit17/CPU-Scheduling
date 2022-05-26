#include<stdio.h>
#include<limits.h>

void arrangeArrival(int num, int mat[][6]);
void completionTime(int num, int mat[][6]);
void turnAroundTime(int num, int mat[][6]);
void waitingTime(int num, int mat[][6]);
double avgTAT(int num, int mat[][6]);
double avgWT(int num, int mat[][6]);
void printResult(int num, int mat[][6]);
void sjf(int num, int mat[][6]);

/*
The matrix mat[][6] contains 
  -> process ID at index 0
  -> Arrival time at index 1
  -> Burst Time at index 2
  -> Completion/Finish Time at index 3
  -> Turn Around Time at index 4
  -> Waiting Time at index 5
*/


//arranging processes according to arrival times  
void arrangeArrival(int num, int mat[][6]){
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 5; k++) {
                    
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
    int inReadyQueue = 0;

    //ready array stores which processes are in the ready queue
    //ready[i] = 0 means process i is not yet arrived
    //ready[i] = 1 means process i is arrived and is in ready queue
    //ready[i] = -1 means process i is terminated

    int currTime = mat[0][1];
    
    for(int i = 0; i < num; i++){

        //all the processes arriving at or before currTime must be in ready queue
        for(int j = 0; j < num; j++){
            if(ready[j] == 0 && mat[j][1] <= currTime){ 
                ready[j] = 1;
                inReadyQueue++;
            }
        }

        int shortestTime = INT_MAX;
        int shortestProcess = 0;
        //take the shortest burst time process from those present in ready queue
        for(int j = 0; j < num; j++){
            if(ready[j] == 1 && mat[j][2] < shortestTime){
                shortestTime = mat[j][2];
                shortestProcess = j;
            }
        }

        //the shortestProcess will be assigned the CPU now...
        ready[shortestProcess] = -1;
        currTime += shortestTime;
        mat[shortestProcess][3] = currTime; 
        inReadyQueue--;

        //if ready queue is empty and the currTime is less than the arrival time of remaining processes
        //then currTime must be updated to the arrival time of next process

        if(inReadyQueue == 0){
            //find the minAT = minimum arrival time of remaining process
            //if currTime is less than minAT, currTime <- minAT
            int minAT = INT_MAX;
            for(int j = 0; j < num; j++){
                if(ready[j] == 0){
                    minAT = mat[j][1];
                    break;
                } 
            }

            if(currTime < minAT) currTime = minAT;
        }

    }

    turnAroundTime(num, mat);
    waitingTime(num, mat);
    printResult(num, mat);
}


void turnAroundTime(int num, int mat[][6]){
    for(int i = 0; i < num; i++) mat[i][4] = mat[i][3] - mat[i][1]; //tat = ct - at
}

void waitingTime(int num, int mat[][6]){
    for(int i = 0; i < num; i++) mat[i][5] = mat[i][4] - mat[i][2]; //wt = tat - bt
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

void printResult(int num, int mat[][6]){
    printf("\t\t\t\tShortest Job First Scheduling\n");
    printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Turn Around Time \t Waiting Time\n");
    for(int i = 0; i < num; i++){
        printf("    %2d\t\t\t%d\t     %d\t\t\t%d\t\t\t%d\t\t\t%d\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3], mat[i][4], mat[i][5]);
    }
    printf("Average Turn Around Time : %f\n", avgTAT(num, mat));
    printf("Average Wait Time : %f\n", avgWT(num, mat));
}

void sjf(int num, int mat[][6]){
    arrangeArrival(num, mat);
    completionTime(num, mat);
}


int main(){
   int n;
   printf("Enter the number of processes ");
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
    
    sjf(n, mat);
}