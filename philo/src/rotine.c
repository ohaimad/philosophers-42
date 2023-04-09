/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 09:04:35 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/09 09:10:41 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_usleep(long long ms)
{
	long long	bg;

	bg = current_time_ms();
	while (current_time_ms() - bg < ms)
		usleep(100);
}

void	print_action(t_list *phil, char *action)
{
	pthread_mutex_lock(&phil->data->p);
	if (phil->data->is)
		printf("%lld %d %s\n", current_time_ms() - phil->start_time, phil->id,
			action);
	pthread_mutex_unlock(&phil->data->p);
}

void	*rootine(void *p)
{
	t_list	*phil;

	phil = (t_list *)p;
	while (phil->data->is)
	{
		if (phil->id % 2)
			usleep(100);
		pthread_mutex_lock(&phil->fork);
		print_action(phil, "has taken a fork");
		pthread_mutex_lock(&phil->next->fork);
		print_action(phil, "has taken a fork");
		pthread_mutex_lock(&phil->data->eat);
		phil->last_meal = current_time_ms();
		pthread_mutex_unlock(&phil->data->eat);
		print_action(phil, "is eating");
		my_usleep(phil->data->time_to_eat);
		pthread_mutex_unlock(&phil->fork);
		pthread_mutex_unlock(&phil->next->fork);
		print_action(phil, "is sleeping");
		my_usleep(phil->data->time_to_sleep);
		print_action(phil, "is thinking");
	}
	return (NULL);
}

void	check_death(t_list *phil)
{
	while (1)
	{
		pthread_mutex_lock(&phil->data->eat);
		if ((current_time_ms() - phil->last_meal) > phil->data->time_to_die)
		{
			pthread_mutex_lock(&phil->data->p);
			printf("%lld %d is dead\n", current_time_ms() - phil->start_time,
				phil->id);
			phil->data->is = 0;
			break ;
		}
		pthread_mutex_unlock(&phil->data->eat);
		phil = phil->next;
	}
}
