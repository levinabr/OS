#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

void generateReference(int ref[], int n) {
    for (int i = 0; i < n; i++) {
        ref[i] = rand() % 10;
    }
}

/* FIFO */
int fifo(int ref[], int n, int frames) {
    int frame[10], front = 0, faults = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[front] = ref[i];
            front = (front + 1) % frames;
            faults++;
        }
    }
    return faults;
}

/* LRU */
int lru(int ref[], int n, int frames) {
    int frame[10], time[10];
    int faults = 0, t = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                time[j] = ++t;
                break;
            }
        }

        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[lru_index])
                    lru_index = j;
            }

            frame[lru_index] = ref[i];
            time[lru_index] = ++t;
            faults++;
        }
    }
    return faults;
}

/* Optimal */
int optimal(int ref[], int n, int frames) {
    int frame[10];
    int faults = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = -1, farthest = i + 1;

            for (int j = 0; j < frames; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == ref[k])
                        break;
                }

                if (k > farthest) {
                    farthest = k;
                    pos = j;
                }

                if (k == n) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
                pos = 0;

            frame[pos] = ref[i];
            faults++;
        }
    }
    return faults;
}

/* MAIN */
int main() {
    int n, frames;
    int ref[MAX];

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    printf("Enter number of frames (1-7): ");
    scanf("%d", &frames);

    srand(1);  // fixed output (important for online compiler)

    generateReference(ref, n);

    printf("\nReference String:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", ref[i]);

    printf("\n");

    printf("\nPage Faults:\n");
    printf("FIFO: %d\n", fifo(ref, n, frames));
    printf("LRU: %d\n", lru(ref, n, frames));
    printf("Optimal: %d\n", optimal(ref, n, frames));

    return 0;
}
