#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // Implementing: wait, obtain mutex, wait, release mutex as described by thread_data structure
    	
	struct thread_data* thread_args = (struct thread_data *) thread_param;
		

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{

    // Allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread using threadfunc() as entry point.

    return false;
}

