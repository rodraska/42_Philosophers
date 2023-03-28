#include "philo.h"

void function()
{
    int i;

    i = 0;
    while (i < 104009)
        i++;
}

int main(void)
{
    struct timeval start_time;
    struct timeval end_time;
    double start;
    double end;
    double  time_taken;

    gettimeofday(&start_time, NULL);
    usleep(5);
    gettimeofday(&end_time, NULL);

    start = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
    time_taken = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_usec - start_time.tv_usec) / 1000.0;
    printf("start time: %f\n", start);
    printf("time taken: %f\n", time_taken);
    
    return (0);
}