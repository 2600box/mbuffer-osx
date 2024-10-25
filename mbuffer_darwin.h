#ifndef MBUFFER_DARWIN_H
#define MBUFFER_DARWIN_H

#include <dispatch/dispatch.h>
#include <time.h>  // For clock_gettime

/*
 * Custom semaphore types and functions for macOS.
 */

typedef dispatch_semaphore_t mbuffer_sem_t;

static inline int mbuffer_sem_init(mbuffer_sem_t *sem, int pshared, unsigned int value)
{
    // pshared is ignored as GCD semaphores are not shared between processes
    *sem = dispatch_semaphore_create(value);
    return (*sem == NULL) ? -1 : 0;
}

static inline int mbuffer_sem_destroy(mbuffer_sem_t *sem)
{
    // No explicit destroy function; set the semaphore to NULL
    *sem = NULL;
    return 0;
}

static inline int mbuffer_sem_wait(mbuffer_sem_t *sem)
{
    // Wait indefinitely
    return (dispatch_semaphore_wait(*sem, DISPATCH_TIME_FOREVER) == 0) ? 0 : -1;
}

static inline int mbuffer_sem_post(mbuffer_sem_t *sem)
{
    dispatch_semaphore_signal(*sem);
    return 0;
}

static inline int mbuffer_sem_getvalue(mbuffer_sem_t *sem, int *value)
{
    // GCD semaphores do not support getting the current value directly
    // Return 0 or implement additional logic if necessary
    *value = 0;  // Alternatively, maintain a separate counter
    return 0;
}

#endif  // MBUFFER_DARWIN_H
