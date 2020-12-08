#ifndef RW_HPP
#define RW_HPP

#include <pthread.h>
#include <string>

#define NUM_READER 10
#define NUM_WRITER 12

typedef struct s_params
{
    pthread_mutex_t mutex;
    char            *buff;

} t_params;

// main.cpp
int         error_msg(std::string block, std::string msg, int i);
t_params    *init_params();

// threads_process.cpp
void    create_threads(pthread_t *th_reader, pthread_t *th_writer, t_params *params);
void    wait_threads(pthread_t *th_reader, pthread_t *th_writer);

// workers.cpp
void    *reader(void *buff);
void    *writer(void *buff);

#endif
