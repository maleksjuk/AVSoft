#include "rw.hpp"

int error_msg(std::string block, std::string msg, int i)
{
    printf("\033[31m[error]\033[m %s: %s", block.c_str(), msg.c_str());
    if (i > -1)
        printf(" (number: %d)", i);
    printf("\n");
    return 1;
}

t_params *init_params()
{
    t_params    *params;
    int         t = 0;

    if (!(params = (t_params *)malloc(sizeof(t_params))))
        exit(error_msg("params", "memory not allocated", -1));

    if (!(params->buff = (char *)malloc(sizeof(char) * (NUM_WRITER + 1))))
        exit(error_msg("params->buff", "memory not allocated", -1));

    memset(params->buff, '\0', NUM_WRITER + 1);

    if ((t = pthread_mutex_init(&params->mutex, NULL)) > 0)
        exit(error_msg("init", "pthread_mutex_init error", t));
    
    return params;
}

int main()
{
    int         i;
    t_params    *params;
    pthread_t   th_reader[NUM_READER];
    pthread_t   th_writer[NUM_WRITER];

    printf("\033[33m===[BEGIN]===\033[m\n");

    params = init_params();
    memset(th_reader, 0, sizeof(pthread_t) * NUM_READER);
    memset(th_writer, 0, sizeof(pthread_t) * NUM_WRITER);

    create_threads(th_reader, th_writer, params);
    wait_threads(th_reader, th_writer);

    pthread_mutex_destroy(&params->mutex);
    free(params->buff);
    free(params);

    printf("\033[33m===[END]===\033[m\n");
    return 0;
}
