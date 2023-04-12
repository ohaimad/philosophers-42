/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 09:11:25 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/12 16:16:48 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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
	if(!(str[i] >= '0' && str[i] <= '9'))
		return(-1);
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

void	check_death(t_list *phil)
{
	while (1)
	{
		pthread_mutex_lock(&phil->data->luck);
		if ((current_time_ms() - phil->last_meal) > phil->data->time_to_die)
		{
			printf("%lld %d is dead\n", current_time_ms() - phil->start_time,
				phil->id);
			phil->data->is = 0;
			break ;
		}
		pthread_mutex_unlock(&phil->data->luck);
		pthread_mutex_lock(&phil->data->luck);
		if (phil->data->check == phil->data->philo_nb)
		{
			phil->data->is = 0;
			break ;
		}
		pthread_mutex_unlock(&phil->data->luck);
		phil = phil->next;
	}
}
