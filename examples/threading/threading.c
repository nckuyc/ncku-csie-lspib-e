#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <erno.h>
#include <time.h>  // usleep() has been deprecated so using nanosleep()
#include <math.h>
#include <string.h>

#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // Implementing: wait, obtain mutex, wait, release mutex as described by thread_data structure
    	
	struct thread_data* thread_args = (struct thread_data *) thread_param;
	
	// First we wait for specified time to obtain mutex 
	struct timespec wait_obtain;
	wait_obtain_sec = 0;
	wait_obtain_nsec = (int)(thread_args->wait_to_obtain_mutex) * 1e6;
	DEBUG_LOG("Thread is sleeping for %d milliseconds", thread_args->wait_to_obtain_mutex);

	if (nanosecond(&wait_obtain, NULL) == -1)
	{
		if (errno == EINTR)
			ERROR_LOG("Sleep interrupted: %s", strerror(errno));
		else
			ERROR_LOG("Sleep failed: %s", strerror(errno));
	}

	// Let's obtain/lock the mutex for thread_args struct
	int rc = pthread_mutex_lock(&threads_args->mutex);


    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{

    // Allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread using threadfunc() as entry point.

    return false;
}

