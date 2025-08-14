// Nevin Abraham
// 1032233449
// OS Assignment 03 - FCFS 

#include <stdio.h>

int main() {
    int n, i;
    float avgWT = 0, avgTAT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n], arrival[n], burst[n], waiting[n], turnaround[n], completion[n];

    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrival[i]);
        printf("Burst Time: ");
        scanf("%d", &burst[i]);
    }

    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                int temp;

                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    completion[0] = arrival[0] + burst[0];
    turnaround[0] = completion[0] - arrival[0];
    waiting[0] = turnaround[0] - burst[0];

    for (i = 1; i < n; i++) {
        if (arrival[i] > completion[i - 1]) {
            completion[i] = arrival[i] + burst[i];
        } else {
            completion[i] = completion[i - 1] + burst[i];
        }
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", process[i], arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
        avgWT += waiting[i];
        avgTAT += turnaround[i];
    }

    avgWT /= n;
    avgTAT /= n;

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f", avgTAT);

    printf("\n\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("  P%d  ", process[i]);
    }
    printf("\n");
    printf("%d", arrival[0]);
    for (i = 0; i < n; i++) {
        printf("    %d", completion[i]);
    }

    return 0;
}



/*
============== OUTPUT ===================
Enter the number of processes: 4

Process 1
Arrival Time: 0 
Burst Time: 12

Process 2
Arrival Time: 1
Burst Time: 21

Process 3
Arrival Time: 2
Burst Time: 32

Process 4
Arrival Time: 5
Burst Time: 21

Process	Arrival	Burst	Completion	Turnaround	Waiting
P1	0	12	12		12		0
P2	1	21	33		32		11
P3	2	32	65		63		31
P4	5	21	86		81		60

Average Waiting Time: 25.50
Average Turnaround Time: 47.00

Gantt Chart:
  P1    P2    P3    P4  
0    12    33    65    86
*/

