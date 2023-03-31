/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:55:41 by ohaimad           #+#    #+#             */
/*   Updated: 2023/03/31 21:48:17 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_list	*last_of_us(t_list *lst)
{
	t_list	*head;

	head = lst;

	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void    philos(t_data *data, int id)
{
	int i;

	data->phil = NULL; 
	i = 1;
	while(id-- >= 1)
    	ft_lstadd_back(&data->phil, ft_lstnew(i++));
	last_of_us(data->phil)->next = data->phil;
}

void	*test(void *p)
{
	t_data	*data;

	data = (t_data *)p;

	printf ("anaaa %d\n", data->phil->id);
	return(NULL);
}

void	philo_pro_max(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_create(&data->thr[i], NULL, test, data);
		pthread_join(data->thr[i], NULL);
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

	if (ac == 5 || ac == 6)
	{
		if (fill_data(&data, ac - 1, av + 1))
			return (printf("Bad argument\n"), 1);
		philos(&data, ft_atoi(av[1]));
		philo_pro_max(&data);
		// while (data.phil)
		// {
		// 	printf("----->%d\n", data.phil->id);
		// 	data.phil = data.phil->next;
		// }
		// printf("%ld\n", data.philo_nb); 
		// printf("%ld\n", data.time_to_die);
		// printf("%ld\n", data.time_to_eat);
		// printf("%ld\n", data.time_to_sleep);
		// printf("%ld\n", data.philo_must_eat);
	}
	else
		return (printf("Bad argument\n"), 1);
	return (0);
}
