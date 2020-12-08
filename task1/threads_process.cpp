#include "rw.hpp"

void create_threads(pthread_t *th_reader, pthread_t *th_writer, t_params *params)
{
    int i = 0;
    while (i < NUM_READER || i < NUM_WRITER)
    {
        if (i < NUM_READER)
            if (pthread_create(&th_reader[i], NULL, reader, params))
                error_msg("reader", "thread not created", i);

        if (i < NUM_WRITER)
            if (pthread_create(&th_writer[i], NULL, writer, params))
                error_msg("writer", "thread not created", i);

        i++;
    }
}

void wait_threads(pthread_t *th_reader, pthread_t *th_writer)
{
    int i = 0;
    while (i < NUM_READER || i < NUM_WRITER)
    {
        if (i < NUM_READER && th_reader[i])
            if (pthread_join(th_reader[i], NULL))
                error_msg("reader", "thread not joined", i);

        if (i < NUM_WRITER && th_writer[i])
            if (pthread_join(th_writer[i], NULL))
                error_msg("writer", "thread not joined", i);

        i++;
    }
}