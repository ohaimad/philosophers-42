/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:55:41 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/06 22:11:41 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_list	*ft_lst_last(t_list *lst)
{
	t_list	*head;

	head = lst;
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	philos(t_data *data, int id)
{
	int	i;

	data->phil = NULL;
	i = 1;
	while (id-- >= 1)
		ft_lstadd_back(&data->phil, ft_lstnew(i++, data));
	ft_lst_last(data->phil)->next = data->phil;
}

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
void	*printing(void *p)
{
	t_list	*phil;

	phil = (t_list *)p;
	while (phil->data->is)
	{
		if (phil->id % 2)
			usleep(100);
		pthread_mutex_lock(&phil->fork);
		pthread_mutex_lock(&phil->data->p);
		if (phil->data->is)
			printf("%lld %d has taken a fork\n", current_time_ms()
					- phil->start_time, phil->id);
		pthread_mutex_unlock(&phil->data->p);
		pthread_mutex_lock(&phil->next->fork);
		pthread_mutex_lock(&phil->data->p);
		if (phil->data->is)
			printf("%lld %d has taken a fork\n", current_time_ms()
					- phil->start_time, phil->id);
		pthread_mutex_unlock(&phil->data->p);
		pthread_mutex_lock(&phil->data->eat);
		phil->last_meal = current_time_ms();
		pthread_mutex_unlock(&phil->data->eat);
		pthread_mutex_lock(&phil->data->p);
		if (phil->data->is)
			printf("%lld %d is eating\n", current_time_ms() - phil->start_time,
					phil->id);
		pthread_mutex_unlock(&phil->data->p);
		my_usleep(phil->data->time_to_eat);
		pthread_mutex_unlock(&phil->fork);
		pthread_mutex_unlock(&phil->next->fork);
		pthread_mutex_lock(&phil->data->p);
		if (phil->data->is)
			printf("%lld %d is sleeping\n", current_time_ms()
					- phil->start_time, phil->id);
		pthread_mutex_unlock(&phil->data->p);
		my_usleep(phil->data->time_to_sleep);
		pthread_mutex_lock(&phil->data->p);
		if (phil->data->is)
			printf("%lld %d is thinking\n", current_time_ms()
					- phil->start_time, phil->id);
		pthread_mutex_unlock(&phil->data->p);
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
void	philo_pro_max(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_create(&data->thr[i], NULL, printing, data->phil);
		data->phil = data->phil->next;
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_detach(data->thr[i]);
		i++;
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
		data->philo_must_eat = ft_atoi(av[4]);
		if (data->philo_must_eat < 0)
			return (1);
	}
	if (data->philo_nb < 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	data.is = 1;
	pthread_mutex_init(&data.p, NULL);
	pthread_mutex_init(&data.eat, NULL);
	ft_design();
	if (ac == 5 || ac == 6)
	{
		i = 0;
		if (fill_data(&data, ac - 1, av + 1))
			return (printf("Bad argument\n"), 1);
		philos(&data, ft_atoi(av[1]));
		philo_pro_max(&data);
		check_death(data.phil);
		while (data.thr[i])
			pthread_detach(data.thr[i++]);
	}
	else
		return (printf("Bad argument\n"), 1);
	return (0);
}
