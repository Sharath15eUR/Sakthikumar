#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

// Global control flag for threads
volatile sig_atomic_t keep_running = 1;

// Signal handler for SIGINT (Ctrl + C)
void sigint_handler(int sig) {
    printf("\nSIGINT received. Ignoring and continuing execution...\n");
    keep_running = 0;
}

// Function to check if a number is prime
int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Thread A: Computes sum of first N prime numbers
void* threadA_func(void* arg) {
    int N = *(int*)arg;
    int count = 0, num = 2, sum = 0;

    printf("Thread A: Starting computation of prime numbers...\n");

    while (count < N && keep_running) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    if (keep_running)
        printf("Thread A: Sum of first %d prime numbers is %d\n", N, sum);
    else
        printf("Thread A: Interrupted. Partial sum = %d\n", sum);

    pthread_exit(NULL);
}

// Thread B: Prints message every 2 seconds for 100 seconds
void* threadB_func(void* arg) {
    time_t start = time(NULL);
    printf("Thread B: Started...\n");

    while (keep_running && time(NULL) - start < 100) {
        printf("Thread 1 running\n");
        sleep(2);
    }

    printf("Thread B: Finished.\n");
    pthread_exit(NULL);
}

// Thread C: Prints message every 3 seconds for 100 seconds
void* threadC_func(void* arg) {
    time_t start = time(NULL);
    printf("Thread C: Started...\n");

    while (keep_running && time(NULL) - start < 100) {
        printf("Thread 2 running\n");
        sleep(3);
    }

    printf("Thread C: Finished.\n");
    pthread_exit(NULL);
}

int main() {
    int N;
    pthread_t threadA, threadB, threadC;

    // Set up signal handler
    signal(SIGINT, sigint_handler);

    // Get input
    printf("Enter the value of N (for prime sum): ");
    scanf("%d", &N);

    // Start real-time tracking
    time_t begin = time(NULL);

    // Create threads
    pthread_create(&threadA, NULL, threadA_func, &N);
    pthread_create(&threadB, NULL, threadB_func, NULL);
    pthread_create(&threadC, NULL, threadC_func, NULL);

    // Wait for threads to finish
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // End time and calculate duration
    time_t end = time(NULL);
    double elapsed_time = difftime(end, begin);
    printf("Main: Total execution time = %.2f seconds\n", elapsed_time);

    return 0;
}
