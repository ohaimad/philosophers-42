/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:55:41 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/12 16:37:14 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_destroy(t_list *phil)
{
	pthread_mutex_destroy(&phil->data->p);
	pthread_mutex_destroy(&phil->data->eat);
	pthread_mutex_destroy(&phil->data->luck);
}

int check_digit(int ac, char **av)
{
	int i = 1;
	int j = 0;
	if (ac < 5 && ac > 6)
		return(-1);
	while(av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if(!(av[i][j] >= '0' && av[i][j] <= '9'))
				return(-1);
			j++;
		}
		i++;
	}
	return(0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	data.is = 1;
	data.check = 0;
	i = 0;
	ft_design();
	if (check_digit(ac, av))
		return (printf("Bad argument\n"), 1);
	pthread_mutex_init(&data.p, NULL);
	pthread_mutex_init(&data.eat, NULL);
	pthread_mutex_init(&data.luck, NULL);
	if (fill_data(&data, ac - 1, av + 1))
		return (printf("Bad argument\n"), 1);
	philos(&data, ft_atoi(av[1]));
	creat_philos(&data);
	check_death(data.phil);
	ft_destroy(data.phil);
	return (0);
}
