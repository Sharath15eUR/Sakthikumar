#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Thread A: Calculate sum of first N prime numbers
void* threadA_func(void* arg) {
    int N = *(int*)arg;
    int count = 0, num = 2, sum = 0;
    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }
    printf("Thread A: Sum of first %d prime numbers is %d\n", N, sum);
    pthread_exit(NULL);
}

// Thread B: Print message every 2 seconds for 100 seconds
void* threadB_func(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start < 100) {
        printf("Thread 1 running\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

// Thread C: Print message every 3 seconds for 100 seconds
void* threadC_func(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start < 100) {
        printf("Thread 2 running\n");
        sleep(3);
    }
    pthread_exit(NULL);
}

int main() {
    int N;
    printf("Enter value for N: ");
    scanf("%d", &N);

    pthread_t threadA, threadB, threadC;

    // Create threads
    pthread_create(&threadA, NULL, threadA_func, &N);
    pthread_create(&threadB, NULL, threadB_func, NULL);
    pthread_create(&threadC, NULL, threadC_func, NULL);

    // Wait for threads to finish
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    return 0;
}
