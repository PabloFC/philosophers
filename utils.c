#include "philo.h"

long long timestamp(void)
{
    struct timeval tv;
    long long ms;

    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    return (ms);
}

void ft_usleep(int ms)
{
    long long start;

    start = timestamp();
    while ((timestamp() - start) < ms)
        usleep(100);
}

int ft_atoi(const char *str)
{
    int sign;
    long result;

    sign = 1;
    result = 0;
    while ((*str >= 9 && *str <= 13) || *str == ' ')
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (sign * result);
}
