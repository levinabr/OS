#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int isFound(int page, int frames[], int f_count) {
    for (int i = 0; i < f_count; i++) {
        if (frames[i] == page) return 1;
    }
    return 0;
}
int main(int argc, char *argv[]) {
    int n, max_f;
    if (argc == 3) {
        n = atoi(argv[1]);
        max_f = atoi(argv[2]);
    } else {
        // Fallback for Online Compilers
        printf("Enter length of reference string: ");
        scanf("%d", &n);
        printf("Enter max number of frames: ");
        scanf("%d", &max_f);
    }

    int ref[n];
    srand(time(NULL));
    printf("\nReference String: ");
    for (int i = 0; i < n; i++) {
        ref[i] = rand() % 10; 
        printf("%d ", ref[i]);
    }

    printf("\n\n%-8s | %-8s | %-8s | %-8s\n", "Frames", "FIFO", "LRU", "OPT");
    printf("--------------------------------------\n");
    for (int f = 1; f <= max_f; f++) {
        int fifo_f = 0, lru_f = 0, opt_f = 0;
        int frames[f], time_used[f];
        for (int i = 0; i < f; i++) frames[i] = -1;
        int next = 0;
        for (int i = 0; i < n; i++) {
            if (!isFound(ref[i], frames, f)) {
                frames[next] = ref[i];
                next = (next + 1) % f;
                fifo_f++;
            }
        }
        for (int i = 0; i < f; i++) { frames[i] = -1; time_used[i] = -1; }
        for (int i = 0; i < n; i++) {
            int found_idx = -1;
            for (int j = 0; j < f; j++) if (frames[j] == ref[i]) found_idx = j;
            if (found_idx != -1) {
                time_used[found_idx] = i; 
            } else {
                int victim = 0;
                for (int j = 1; j < f; j++) {
                    if (frames[j] == -1) { victim = j; break; }
                    if (time_used[j] < time_used[victim]) victim = j;
                }
                frames[victim] = ref[i];
                time_used[victim] = i;
                lru_f++;
            }
        }
        for (int i = 0; i < f; i++) frames[i] = -1;
        for (int i = 0; i < n; i++) {
            if (!isFound(ref[i], frames, f)) {
                int victim = -1;
                for (int j = 0; j < f; j++) if (frames[j] == -1) { victim = j; break; }
                if (victim == -1) {
                    int farthest = -1;
                    for (int j = 0; j < f; j++) {
                        int k;
                        for (k = i + 1; k < n; k++) if (frames[j] == ref[k]) break;
                        if (k > farthest) { farthest = k; victim = j; }
                    }
                }
                frames[victim] = ref[i];
                opt_f++;
            }
        }
        printf("%-8d | %-8d | %-8d | %-8d\n", f, fifo_f, lru_f, opt_f);
    }
    return 0;
}
