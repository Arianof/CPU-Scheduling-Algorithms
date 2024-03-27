#include <stdio.h>
#include "CPU_Sch_Struct.h"
#include "stdlib.h"
int main() {
    int sch_case;
    printf("which CPU scheduling do you want to execute?\n1. FCFS\n2. SFJ\n3. Priority\n4. Robin Round\n");
    scanf("%d", &sch_case);
    if (sch_case == 1){
        int n;
        struct CPU_Sdl FCFS;
        printf("Enter number of processes:\n");
        scanf("%d", &n);
        printf("Enter IDs of processes:\n");
        for (int i = 0; i < n; ++i) {
            scanf("%d", &FCFS.pid[i]);
        }
        printf("Enter burst time of all processes:\n");
        for (int i = 0; i < n; ++i) {
            scanf("%d", &FCFS.bt[i]);
        }
        FCFS.wt[0] = 0;
        for (int i = 1; i < n; ++i) {
            FCFS.wt[i] = FCFS.wt[i - 1] + FCFS.bt[i - 1];
        }
        double twt = 0.0;
        double tat = 0.0;
        for (int i = 0; i < n; ++i) {
            FCFS.TurnaroundTime[i] = FCFS.wt[i] + FCFS.bt[i];
            //total waiting time
            twt += FCFS.wt[i];
            //total turnaroundTime
            tat += FCFS.wt[i] + FCFS.bt[i];
        }
        double awt = twt/n;
        double aat = tat/n;
        printf("Process ID      Burst time      Waiting Time    TurnAround time\n");
        for (int i = 0; i < n; ++i) {
            printf("%d \t\t", FCFS.pid[i]);
            printf("%d \t\t", FCFS.bt[i]);
            printf("%d \t\t", FCFS.wt[i]);
            printf("%d \t\t", FCFS.TurnaroundTime[i]);
            printf("\n");
        }
        printf("average waiting time is: %f \n", awt);
        printf("average turnAround time is: %f", aat);

    }
    //SJF algorithm
    else if(sch_case == 2){
        
    }
    return 0;
}
