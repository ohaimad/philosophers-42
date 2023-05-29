/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 09:04:35 by ohaimad           #+#    #+#             */
/*   Updated: 2023/05/29 19:31:19 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher_bonus.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_list *phil, char *action)
{

	if (phil->data->is)
		printf("%lld %d %s\n", current_time_ms() - phil->start_time, phil->id,
			action);
}

void	check_optional(t_list *phil)
{
	if (phil->data->optional == 1)
	{

		phil->nb_eat++;
		if (phil->nb_eat == phil->data->philo_must_eat)
			phil->data->check++;

	}
}

void	pick_up_forks(t_list *phil)
{
	print_action(phil, "has taken a fork");
	print_action(phil, "has taken a fork");
}

void	*rootine(void *p)
{
	t_list	*phil;

	phil = (t_list *)p;
	if (phil->id % 2)
		usleep (100);
	while (1)
	{
		sem_wait(phil->forks);
		sem_wait(phil->forks);
		pick_up_forks(phil);
		phil->last_meal = current_time_ms();
		print_action(phil, "is eating");
		check_optional(phil);
		my_usleep(phil->data->time_to_eat);
		sem_post(phil->forks);
		sem_post(phil->forks);
		print_action(phil, "is sleeping");
		my_usleep(phil->data->time_to_sleep);
		print_action(phil, "is thinking");
	}
	return (NULL);
}
