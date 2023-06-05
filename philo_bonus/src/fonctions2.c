/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 09:11:25 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/05 17:12:14 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	signe;
	int	res;

	res = 0;
	signe = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		res = res * 10;
		res = res + str[i] - '0';
		i++;
	}
	if ((res * signe) > 2147483647 || (res * signe) < -2147483648)
		return (-1);
	return (res * signe);
}

int	check_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac != 5 && ac != 6)
		return (-1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	my_usleep(long long ms, t_list *phil)
{
	long long	bg;

	bg = current_time_ms();
	while (current_time_ms() - bg < ms)
	{
		if ((current_time_ms() - phil->last_meal) > phil->data->time_to_die)
		{
			sem_wait(phil->my_print);
			printf("%lld %d is dead\n", current_time_ms() - phil->start_time,
				phil->id);
			// sem_post(phil->my_print);
			exit (0);
		}
		if (phil->data->check == phil->data->philo_nb)
			exit (0);
		usleep(100);
	}
}
// void	check_death(t_list *phil)
// {
// 	while (1)
// 	{
// 		if ((current_time_ms() - phil->last_meal) > phil->data->time_to_die)
// 		{
// 			printf("%lld %d is dead\n", current_time_ms() - phil->start_time,
// 				phil->id);
// 			exit (0);
// 		}
// 		if (phil->data->check == phil->data->philo_nb)
// 			exit (0);
// 		phil = phil->next;
// 	}
// }
