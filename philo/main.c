/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:55:41 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/10 20:05:26 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	
	data.is = 1;
	data.check = 0;
	pthread_mutex_init(&data.p, NULL);
	pthread_mutex_init(&data.eat, NULL);
	pthread_mutex_init(&data.luck, NULL);
	ft_design();
	if (ac == 5 || ac == 6)
	{
		i = 0;
		if (fill_data(&data, ac - 1, av + 1))
			return (printf("Bad argument\n"), 1);
		philos(&data, ft_atoi(av[1]));
		creat_philos(&data);
		check_death(data.phil);
		while (data.thr[i])
			pthread_detach(data.thr[i++]);
	}
	else
		return (printf("Bad argument\n"), 1);
	return (0);
}
