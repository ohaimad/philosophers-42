/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:55:41 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/01 01:28:06 by ohaimad          ###   ########.fr       */
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

void    philos(t_data *data, t_tmp *tmp, int id)
{
	int i;

	data->phil = NULL; 
	i = 1;
	while(id-- >= 1)
    	ft_lstadd_back(&data->phil, ft_lstnew(i++, tmp));
	ft_lst_last(data->phil)->next = data->phil;
}

void	*printing(void *p)
{
	t_list	*phil;
	phil = (t_list *)p;
	while (phil->tmp->is)
	{
		if (phil->id % 2)
			usleep(1000);
		pthread_mutex_lock(&phil->fork);
		
		pthread_mutex_lock(&phil->tmp->p);
		printf ("philo %d has taken a fork\n", phil->id);
		pthread_mutex_unlock(&phil->tmp->p);
		
		pthread_mutex_lock(&phil->next->fork);
		
		pthread_mutex_lock(&phil->tmp->p);
		printf ("philo %d has taken a fork\n", phil->id);
		pthread_mutex_unlock(&phil->tmp->p);
		
		pthread_mutex_lock(&phil->tmp->p);
		printf ("philo %d is eating\n", phil->id);
		pthread_mutex_unlock(&phil->tmp->p);

		usleep(200 * 1000);
		pthread_mutex_unlock(&phil->fork);
		pthread_mutex_unlock(&phil->next->fork);
		
		pthread_mutex_lock(&phil->tmp->p);
		printf ("philo %d is sleeping\n", phil->id);
		pthread_mutex_unlock(&phil->tmp->p);
		
		usleep(200 * 1000);
		
		pthread_mutex_lock(&phil->tmp->p);
		printf ("philo %d is thinking\n", phil->id);
		pthread_mutex_unlock(&phil->tmp->p);
	}
	return(NULL);
}

void	philo_pro_max(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_create(&data->thr[i], NULL, printing, data->phil);
		data->phil = data->phil->next;
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
	if (data->philo_nb < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	t_tmp	tmp;

	tmp.is = 1;
	if (ac == 5 || ac == 6)
	{
		if (fill_data(&data, ac - 1, av + 1))
			return (printf("Bad argument\n"), 1);
		philos(&data, &tmp, ft_atoi(av[1]));
		philo_pro_max(&data);
		int i = 0;

		while(data.thr[i])
			pthread_join(data.thr[i++], NULL);
	}
	else
		return (printf("Bad argument\n"), 1);
	return (0);
}
