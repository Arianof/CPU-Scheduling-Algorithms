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
        int n, pos, temp;
        struct CPU_Sdl SJF;
        printf("Enter number of processes:\n");
        scanf("%d", &n);
        printf("Enter IDs of processes:\n");
        for (int i = 0; i < n; ++i)
            scanf("%d", &SJF.pid[i]);
        printf("Enter burst time of all processes:\n");
        for (int i = 0; i < n; ++i)
            scanf("%d", &SJF.bt[i]);

        //sort processes base of their burst time
        for (int i = 0; i < n; ++i) {
            pos = i;
            for (int j = i + 1; j < n; ++j)
                if(SJF.bt[j] < SJF.bt[pos])
                    pos = j;
            temp = SJF.bt[pos];
            SJF.bt[pos] = SJF.bt[i];
            SJF.bt[i] = temp;

            temp = SJF.pid[pos];
            SJF.pid[pos] = SJF.pid[i];
            SJF.pid[i] = temp;
        }

        //calculating waiting time and turnaround time
        SJF.wt[0] = 0;
        double twt = 0;
        double total_tat = 0;
        for (int i = 1; i < n; ++i) {
            SJF.wt[i] = SJF.bt[i - 1] + SJF.wt[i - 1];
            twt += SJF.wt[i];
        }
        for (int i = 0; i < n; ++i) {
            SJF.TurnaroundTime[i] = SJF.bt[i] + SJF.wt[i];
            total_tat += SJF.TurnaroundTime[i];
        }

        printf("Process ID      Burst time      Waiting Time    TurnAround time\n");
        for (int i = 0; i < n; ++i) {
            printf("%d \t\t", SJF.pid[i]);
            printf("%d \t\t", SJF.bt[i]);
            printf("%d \t\t", SJF.wt[i]);
            printf("%d \t\t", SJF.TurnaroundTime[i]);
            printf("\n");
        }
        printf("average waiting time is: %f \n", twt/n);
        printf("average turnAround time is: %f", total_tat/n);
    }
    //priority algorithms
    else if(sch_case == 3){
        int n, pos, temp;
        struct CPU_Sdl P;
        printf("Enter number of processes:\n");
        scanf("%d", &n);
        printf("Enter IDs of processes:\n");
        for (int i = 0; i < n; ++i)
            scanf("%d", &P.pid[i]);
        printf("Enter burst time of all processes:\n");
        for (int i = 0; i < n; ++i)
            scanf("%d", &P.bt[i]);
        printf("Enter Priority of all processes\n");
        for (int i = 0; i < n; ++i)
            scanf("%d", &P.priority[i]);

        //sort processes base of higher priority
        for (int i = 0; i < n; ++i) {
            pos = i;
            for (int j = i + 1; j < n; ++j)
                if(P.priority[j] > P.priority[pos])
                    pos = j;
            temp = P.priority[pos];
            P.priority[pos] = P.priority[i];
            P.priority[i] = temp;

            temp = P.pid[pos];
            P.pid[pos] = P.pid[i];
            P.pid[i] = temp;

            temp = P.bt[pos];
            P.bt[pos] = P.bt[i];
            P.bt[i] = temp;
        }
        //calculating waiting time and turnaround time of all processes
        P.wt[0] = 0;
        double twt = 0;
        double total_tat = 0;
        for (int i = 1; i < n; ++i) {
            P.wt[i] = P.wt[i - 1] + P.bt[i - 1];
            twt += P.wt[i];
        }
        for (int i = 0; i < n; ++i) {
            P.TurnaroundTime[i] = P.bt[i] + P.wt[i];
            total_tat += P.TurnaroundTime[i];
        }

        printf("Process ID      Priority      Burst time      Waiting Time    TurnAround time\n");
        for (int i = 0; i < n; ++i) {
            printf("%d \t\t", P.pid[i]);
            printf("%d \t\t", P.priority[i]);
            printf("%d \t\t", P.bt[i]);
            printf("%d \t\t", P.wt[i]);
            printf("%d \t\t", P.TurnaroundTime[i]);
            printf("\n");
        }
        printf("average waiting time is: %f \n", twt/n);
        printf("average turnAround time is: %f", total_tat/n);
    }
    //robin round algorithm
    else{
        int n, quantum, temp, pos;
        double twt = 0;
        double total_tat = 0;
        struct CPU_Sdl RR;
        printf("Enter number of processes:\n");
        scanf("%d", &n);
        printf("Enter IDs of processes:\n");
        for (int i = 0; i < n; ++i)
            scanf("%d", &RR.pid[i]);
        printf("Enter burst time of all processes:\n");
        for (int i = 0; i < n; ++i)
            scanf("%d", &RR.bt[i]);
        printf("Enter quantum time:\n");
        scanf("%d", &quantum);
        //copy burst time of all processes for calculating waiting time and turnaround time
        int temp_bt[n];
        for (int i = 0; i < n; ++i) {
            temp_bt[i] = RR.bt[i];
        }
        //current time
        int t = 0;
        //keep traversing until all processes are completed
        //calculate waiting time of all processes
        while(1){
            int flag = 1;
            for (int i = 0; i < n; ++i) {
                if(temp_bt[i]){
                    flag = 0;
                    if(temp_bt[i] > quantum){
                        t += quantum;
                        temp_bt[i] -= quantum;
                    }else{
                        t += temp_bt[i];
                        RR.wt[i] = t - RR.bt[i];
                        temp_bt[i] = 0;
                        twt += RR.wt[i];
                    }
                }
            }
            if(flag == 1)
                break;
        }
        //calculate turnaround time of all processes
        for (int i = 0; i < n; ++i) {
            RR.TurnaroundTime[i] = RR.bt[i] + RR.wt[i];
            total_tat += RR.TurnaroundTime[i];
        }

        //sort processes base of higher priority
        for (int i = 0; i < n; ++i) {
            pos = i;
            for (int j = i + 1; j < n; ++j)
                if(RR.TurnaroundTime[j] < RR.TurnaroundTime[pos])
                    pos = j;
            temp = RR.TurnaroundTime[pos];
            RR.TurnaroundTime[pos] = RR.TurnaroundTime[i];
            RR.TurnaroundTime[i] = temp;

            temp = RR.pid[pos];
            RR.pid[pos] = RR.pid[i];
            RR.pid[i] = temp;

            temp = RR.bt[pos];
            RR.bt[pos] = RR.bt[i];
            RR.bt[i] = temp;

            temp = RR.wt[pos];
            RR.wt[pos] = RR.wt[i];
            RR.wt[i] = temp;
        }

        printf("Process ID      Burst time      Waiting Time    TurnAround time\n");
        for (int i = 0; i < n; ++i) {
            printf("%d \t\t", RR.pid[i]);
            printf("%d \t\t", RR.bt[i]);
            printf("%d \t\t", RR.wt[i]);
            printf("%d \t\t", RR.TurnaroundTime[i]);
            printf("\n");
        }
        printf("average waiting time is: %f \n", twt/n);
        printf("average turnAround time is: %f", total_tat/n);
    }
    return 0;
}
