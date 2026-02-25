#include <stdio.h>
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int p[n], a[n], b[n], pr[n];
    int ct[n], tat[n], wt[n], rt[n], done[n];
    int pid_counter = 1;
    for(int i = 0; i < n; i++) {
        p[i] = pid_counter++;
        printf("\nConfiguring Process %d (Auto-assigned PID: %d):\n", i + 1, p[i]);
        printf("Enter Arrival Time : ");
        scanf("%d", &a[i]);
        printf("Enter Burst Time   : ");
        scanf("%d", &b[i]);

        printf("Enter Priority     : ");
        scanf("%d", &pr[i]);

        printf("Process values recorded successfully.\n");
    }
    int time = 0;
    float avg_wt_fcfs = 0;
    for(int i = 0; i < n; i++) {
        if(time < a[i]) time = a[i];
        ct[i] = time + b[i];
        time = ct[i];
        tat[i] = ct[i] - a[i];
        wt[i] = tat[i] - b[i];
        avg_wt_fcfs += wt[i];
    }
    avg_wt_fcfs /= n;
    printf("\n--- FCFS Scheduling Output ---\n");
    printf("\tPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int k=0; k<n; k++) {
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[k], a[k], b[k], ct[k], tat[k], wt[k]);
    }
    printf("Average Waiting Time (FCFS) = %.2f\n", avg_wt_fcfs);
    for(int i = 0; i < n; i++) rt[i] = b[i];
    int complete = 0;
    time = 0;
    float avg_wt_srtf = 0;
    while(complete != n) {
        int shortest = -1, min = 9999;
        for(int i = 0; i < n; i++) {
            if(a[i] <= time && rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                shortest = i;
            }
        }
        if(shortest == -1) { time++; continue; }
        rt[shortest]--;
        time++;
        if(rt[shortest] == 0) {
            complete++;
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - a[shortest];
            wt[shortest] = tat[shortest] - b[shortest];
            avg_wt_srtf += wt[shortest];
        }
    }
    avg_wt_srtf /= n;
    printf("\n--- SRTF (Preemptive) Output ---\n");
    printf("\tPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int k=0; k<n; k++) {
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[k], a[k], b[k], ct[k], tat[k], wt[k]);
    }
    printf("Average Waiting Time (SRTF) = %.2f\n", avg_wt_srtf);
    for(int i = 0; i < n; i++) done[i] = 0;
    time = 0; complete = 0;
    float avg_wt_priority = 0;
    while(complete != n) {
        int highest = -1, maxp = -1;
        for(int i = 0; i < n; i++) {
            if(a[i] <= time && done[i] == 0 && pr[i] > maxp) {
                maxp = pr[i];
                highest = i;
            }
        }
        if(highest == -1) { time++; continue; }
        ct[highest] = time + b[highest];
        time = ct[highest];
        tat[highest] = ct[highest] - a[highest];
        wt[highest] = tat[highest] - b[highest];
        done[highest] = 1;
        complete++;
        avg_wt_priority += wt[highest];
    }
    avg_wt_priority /= n;
    printf("\n--- Non-Preemptive Priority Output ---\n");
    printf("\tPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int k=0; k<n; k++) {
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[k], a[k], b[k], ct[k], tat[k], wt[k]);
    }
    printf("Average Waiting Time (Priority) = %.2f\n", avg_wt_priority);
    for(int i = 0; i < n; i++) rt[i] = b[i];
    time = 0; complete = 0;
    float avg_wt_rr = 0;
    while(complete != n) {
        int executed = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] <= time && rt[i] > 0) {
                executed = 1;
                if(rt[i] > 3) {
                    time += 3;
                    rt[i] -= 3;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    tat[i] = ct[i] - a[i];
                    wt[i] = tat[i] - b[i];
                    avg_wt_rr += wt[i];
                    complete++;
                }
            }
        }
        if(!executed) time++;
    }
    avg_wt_rr /= n;
    printf("\n--- Round Robin (Quantum = 3) Output ---\n");
    printf("\tPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int k=0; k<n; k++) {
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[k], a[k], b[k], ct[k], tat[k], wt[k]);
    }
    printf("Average Waiting Time (RR) = %.2f\n", avg_wt_rr);
    printf("\n--- Overall Comparison ---\n");
    float min_val = avg_wt_fcfs;
    char algo_name[20] = "FCFS";
    if(avg_wt_srtf < min_val) { min_val = avg_wt_srtf; sprintf(algo_name, "SRTF"); }
    if(avg_wt_priority < min_val) { min_val = avg_wt_priority; sprintf(algo_name, "Priority"); }
    if(avg_wt_rr < min_val) { min_val = avg_wt_rr; sprintf(algo_name, "Round Robin"); }
    printf("The best algorithm for this set is %s with an Average WT of %.2f\n", algo_name, min_val);
    return 0;
}
