/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 09:04:35 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/12 17:11:43 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_list *phil, char *action)
{
	pthread_mutex_lock(&phil->data->luck);
	if (phil->data->is)
		printf("%lld %d %s\n", current_time_ms() - phil->start_time, phil->id,
			action);
	pthread_mutex_unlock(&phil->data->luck);
}

void	check_optional(t_list *phil)
{
	if (phil->data->optional == 1)
	{
		pthread_mutex_lock(&phil->data->luck);
		phil->nb_eat++;
		if (phil->nb_eat >= phil->data->philo_must_eat)
			phil->data->check++;
		pthread_mutex_unlock(&phil->data->luck);
	}
}

void	pick_up_forks(t_list *phil)
{
	pthread_mutex_lock(&phil->fork);
	print_action(phil, "has taken a fork");
	pthread_mutex_lock(&phil->next->fork);
	print_action(phil, "has taken a fork");
}

void	*rootine(void *p)
{
	t_list	*phil;

	phil = (t_list *)p;
	while (1)
	{
		pthread_mutex_lock(&phil->data->luck);
		if (!phil->data->is)
			break ;
		pthread_mutex_unlock(&phil->data->luck);
		if (phil->id % 2)
			usleep(100);
		pick_up_forks(phil);
		pthread_mutex_lock(&phil->data->luck);
		phil->last_meal = current_time_ms();
		pthread_mutex_unlock(&phil->data->luck);
		print_action(phil, "is eating");
		my_usleep(phil->data->time_to_eat);
		pthread_mutex_unlock(&phil->fork);
		pthread_mutex_unlock(&phil->next->fork);
		check_optional(phil);
		print_action(phil, "is sleeping");
		my_usleep(phil->data->time_to_sleep);
		print_action(phil, "is thinking");
	}
	return (NULL);
}
