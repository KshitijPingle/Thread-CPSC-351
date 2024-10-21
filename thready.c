// Kshitij Pingle
// kpingle@csu.fullerton.edu
// Date: October 17, 2024
// Description: Program to create a pattern of threads.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>


struct ThreadInfo {
    pthread_t thread_id;
    unsigned int thread_num;
    unsigned int n;
};


// General print function to be called by pthread_create
void * Print(void * arg) {

    // Make a pointer to struct and assign args to it
    struct ThreadInfo * thread_info = arg;
    
    printf("Thread Number : %u Beginning\n", thread_info->thread_num + 1);

    sleep(2);    // Simulate other work

    printf("Thread Number : %u Exiting\n", thread_info->thread_num + 1);
}


// Recursive Print function for Pattern 2
void * Print2(void * arg) {

    // Make a pointer to struct and assign args to it
    struct ThreadInfo * thread_info = arg;
    
    printf("Thread Number : %u Beginning\n", thread_info->thread_num + 1);

    struct ThreadInfo thread_child = *(thread_info);
    thread_child.thread_num++;

    if (thread_info->thread_num < thread_info->n) {

        // Make another thread
        printf("Thread Number : %u Creating Thread %u\n", thread_info->thread_num + 1, thread_child.thread_num + 1);
        pthread_create(&thread_child.thread_id, NULL, Print2, (void *)&thread_child);
        pthread_join(thread_child.thread_id, NULL);
    }

    sleep(2);       // Simulate other work

    printf("Thread Number : %u Exiting\n", thread_info->thread_num + 1);
}


void Pattern1(unsigned int n) {

    pthread_t thread_id;

    // Make struct object
    struct ThreadInfo thread_info;
    thread_info.thread_id = thread_id;
    thread_info.thread_num = 0;
    thread_info.n = n;
    
    for (unsigned int i = 0; i < n; ++i) {

        printf("Main created Thread %d\n", thread_info.thread_num + 1);
        pthread_create(&thread_id, NULL, Print, (void *)&thread_info);

        pthread_join(thread_id, NULL);

        thread_info.thread_num++;
    }
}


void Pattern2(unsigned int n) {

    pthread_t thread_id;

    // Make struct object
    struct ThreadInfo thread_info;
    thread_info.thread_id = thread_id;
    thread_info.thread_num = 0;
    thread_info.n = n - 1;

    printf("Main created Thread %u\n", thread_info.thread_num + 1);
    pthread_create(&thread_id, NULL, Print2, (void *)&thread_info);

    pthread_join(thread_id, NULL);
}


void Pattern3(unsigned int n) {
    printf("Pattern 3 work in progress\n");
}



int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("Incorrect number of arguments passed\n");
        printf("Usage: %s <Pattern Number> <Random Number>\n", argv[0]);
        return 1;
    }

    unsigned int pattern_num = atoi(argv[1]);
    unsigned int n = atoi(argv[2]);

    if ((pattern_num < 1) || (pattern_num > 3)) {
        printf("Wrong Usage, Pattern number should be between 1 and 3\n");
        printf("Usage: %s <Pattern Number> <Random Number>\n", argv[0]);
        return 1;
    }


    // Function pointer
    typedef void (*Pattern)(unsigned int n);

    Pattern pattern;

    switch (pattern_num) {

        case 1:
            pattern = Pattern1;
            break;
    
        case 2:
            pattern = Pattern2;
            break;

        case 3:
            pattern = Pattern3;
            break;
    
        default:
            pattern = Pattern1;
            break;
    }

    pattern(n);
    
    return 0;
}