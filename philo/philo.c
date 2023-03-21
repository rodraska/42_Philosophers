#include "philo.h"

int parse_args(int ac, char **av)
{
    int i;

    i = 0;
    while (++i < ac)
    {
        if (check_digits(av[i]) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if (i == 1 && ft_atoi(av[1]) > 200)
        {
            write(1, "Invalid number of philosophers\n", 31);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {   
        if (parse_args(ac, av) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        else
        {
            write(1, "Success\n", 8);
            return (EXIT_SUCCESS);
        }
    }
    else
    {
        write(1, "Invalid number of arguments\n", 28);
        return (EXIT_FAILURE);
    }
}