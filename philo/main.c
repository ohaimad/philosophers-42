/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:55:41 by ohaimad           #+#    #+#             */
/*   Updated: 2023/03/28 00:31:14 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void    philos(t_list *data, int id)
{
	int i;

	i = 1;
	while(id >= 1)
	{
    	ft_lstadd_back(&data, ft_lstnew(i));
		id--;
	}
	
}

int	fill_data(t_data *data, int ac, char **av)
{
	data->philo_nb = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
	{
		data->must_eat = ft_atoi(av[4]);
		if (data->must_eat < 0)
			return (1);
	}
	if (data->philo_nb < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	// int		ret;

	if (ac == 5 || ac == 6)
	{
		if (fill_data(&data, ac - 1, av + 1))
			return (printf("Bad argument\n"), 1);
		// philos(&data, av[1]);
		printf("%ld\n", data.philo_nb);
		printf("%ld\n", data.time_to_die);
		printf("%ld\n", data.time_to_eat);
		printf("%ld\n", data.time_to_sleep);
		printf("%ld\n", data.must_eat);
	}
	else
		return (printf("Bad argument\n"), 1);
	return (0);
}
