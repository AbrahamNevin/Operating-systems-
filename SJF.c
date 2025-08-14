#include <stdio.h>

int main() {
    int n, i;
    float avgWT = 0, avgTAT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n], arrival[n], burst[n], remaining[n], waiting[n], turnaround[n], completion[n];
    int finished = 0, currentTime = 0, minRemaining, idx;

    // Input
    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrival[i]);
        printf("Burst Time: ");
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
    }

    // SRTF Scheduling
    while (finished < n) {
        idx = -1;
        minRemaining = 1e9;

        // Find process with shortest remaining time among arrived
        for (i = 0; i < n; i++) {
            if (arrival[i] <= currentTime && remaining[i] > 0) {
                if (remaining[i] < minRemaining) {
                    minRemaining = remaining[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process available, CPU idle
            currentTime++;
        } else {
            // Run process for 1 unit of time
            remaining[idx]--;
            currentTime++;

            // If process finishes
            if (remaining[idx] == 0) {
                finished++;
                completion[idx] = currentTime;
                turnaround[idx] = completion[idx] - arrival[idx];
                waiting[idx] = turnaround[idx] - burst[idx];

                avgWT += waiting[idx];
                avgTAT += turnaround[idx];
            }
        }
    }

    // Display table
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", process[i], arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    avgWT /= n;
    avgTAT /= n;

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f", avgTAT);

    return 0;
}

