/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:55:41 by ohaimad           #+#    #+#             */
/*   Updated: 2023/05/29 18:51:39 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	data.is = 1;
	data.check = 0;
	i = 0;
	if (check_digit(ac, av))
		return (printf("Bad argument\n"), 1);
	if (fill_data(&data, ac - 1, av + 1))
		return (printf("Bad argument\n"), 1);
	philos(&data, ft_atoi(av[1]));
	creat_philos(&data);
	return (0);
}
