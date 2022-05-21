#include<stdio.h>

void arrangeArrival(int num, int mat[][6]);
void completionTime(int num, int mat[][6]);
void turnAroundTime(int num, int mat[][6]);
void waitingTime(int num, int mat[][6]);
double avgTAT(int num, int mat[][6]);
double avgWT(int num, int mat[][6]);
void printResult(int num, int mat[][6]);
void fcfs(int num, int mat[][6]);

  
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
    mat[0][3] = mat[0][2] + mat[0][1];
    int currTime = mat[0][3];
    for(int i = 1; i < num; i++){
        if(mat[i][1] > currTime) currTime = mat[i][1];
        mat[i][3] = currTime + mat[i][2];
        currTime = mat[i][3];
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

void printResult(int num, int mat[][6]){
    printf("\t\t\t\tFirst Come First Serve\n");
    printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Turn Around Time \t Waiting Time\n");
    for(int i = 0; i < num; i++){
        printf("    %2d\t\t\t%d\t     %d\t\t\t%d\t\t\t%d\t\t\t%d\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3], mat[i][4], mat[i][5]);
    }
    printf("Average Turn Around Time : %f\n", avgTAT(num, mat));
    printf("Average Wait Time : %f\n", avgWT(num, mat));
}

void fcfs(int num, int mat[][6]){
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
    
    fcfs(n, mat);
}