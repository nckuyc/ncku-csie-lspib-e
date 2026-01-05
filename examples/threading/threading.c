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
	thread_args->thread_complete_success = true;    // by default, set to true. Sets to false on occurrence of any errors.
	
	// First we wait for specified time to obtain mutex
	long ms_obtain = thread_args->wait_to_obtain_mutex;

	struct timespec wait_obtain, wait_obtain_rem;
	wait_obtain.tv_sec = ms_obtain / 1000;		// gets whole second value
	wait_obtain.tv_nsec = (ms_obtain % 1000) * 1000000L;	// converts leftover from "ms/1000" into nanoseconds

	DEBUG_LOG("Thread is sleeping for %d milliseconds", thread_args->wait_to_obtain_mutex);

	while (nanosleep(&wait_obtain, &wait_obtain_rem) == -1)
	{
		if (errno == EINTR){
			DEBUG_LOG("Sleep interrupted: %s", strerror(errno));
			wait_obtain = wait_obtain_rem;
			continue;
		}
		ERROR_LOG("Sleep failed: %s", strerror(errno));
		thread_args->thread_complete_success = false;
		break;
	}

	// Let's lock the mutex for thread_args struct
	int rc = pthread_mutex_lock(&thread_args->mutex);

	if (rc != 0){
		ERROR_LOG("pthread_mutex_lock failed with %d: %s", rc , strerror(rc));
		thread_args->thread_complete_success = false;
		return thread_args;
	}

	// Now let's sleep the thread for a defined time before releasing the mutex
	long ms_release = thread_args->wait_to_release_mutex;

	struct timespec wait_release, wait_release_rem;
	wait_release.tv_sec = ms_release / 1000;
	wait_release.tv_nsec = (ms_release % 1000) * 1000000L;

	DEBUG_LOG("Thread is sleeping for %d milliseconds", thread_args->wait_to_release_mutex);

	while (nanosleep(&wait_release, &wait_release_rem) == -1)
	{	
		if (errno == EINTR){
			DEBUG_LOG("Sleep interrupted: %s", strerror(errno));
			wait_release = wait_release_rem;
			continue;
		}
		ERROR_LOG("Sleep failed: %s", strerror(errno));
		thread_args->thread_complete_success = false;
		break;
	}
	
	rc = pthread_mutex_unlock(&thread_args->mutex);
	if (rc != 0){
		ERROR_LOG("pthread_mutex_unlock failed with %d: %s", rc, strerror(rc));
		thread_args->thread_complete_success = false;
	}

    return thread_args;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{

    // Allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread using threadfunc() as entry point.

    return false;
}

