#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
    sign = 1;
	if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
	num = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	return (num * sign);
}

int check_digits(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < 48 || str[i] > 57)
        {
            write(1, "Invalid argument\n", 17);
            return (EXIT_FAILURE);
        } 
        i++;
    }
    return (EXIT_SUCCESS);
}

t_table *table(void)
{
    static t_table table;

    return (&table);
}

