#include "rw.hpp"

void *reader(void *arg)
{
    t_params    *params = (t_params *) arg;
    int         t = 0;

    if ((t = pthread_mutex_lock(&params->mutex)) > 0)
        error_msg("reader", "pthread_mutex_lock error", t);

    printf("[READ] %s (size: %lu)\n", params->buff, strlen(params->buff));

    if ((t = pthread_mutex_unlock(&params->mutex) > 0))
        error_msg("reader", "pthread_mutex_unlock error", t);

    pthread_exit(NULL);
}

void *writer(void *arg)
{
    t_params    *params = (t_params *) arg;
    int         t = 0;

    if ((t = pthread_mutex_lock(&params->mutex)) > 0)
        error_msg("writer", "pthread_mutex_lock error", t);

    params->buff[strlen(params->buff)] = '.';
    printf("[WRITE] .\n");

    if ((t = pthread_mutex_unlock(&params->mutex)) > 0)
        error_msg("writer", "pthread_mutex_unlock error", t);

    pthread_exit(NULL);
}
