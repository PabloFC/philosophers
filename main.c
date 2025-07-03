#include "philo.h"

int main(int argc, char **argv)
{
    t_rules rules;

    if (init_all(&rules, argc, argv))
        return (1);
    if (start_simulation(&rules))
    {
        cleanup(&rules);
        return (1);
    }
    cleanup(&rules);
    return (0);
}
