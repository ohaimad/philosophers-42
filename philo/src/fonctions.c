/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:46:07 by ohaimad           #+#    #+#             */
/*   Updated: 2023/05/03 12:08:58 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	ft_design(void)
{
	printf("\033[1;31m");
	printf(" ______ _   _ _____ _     _____ \n");
	printf("| ___ \\ | | |_   _| |   |  _  |\n");
	printf("| |_/ / |_| | | | | |   | | | |\n");
	printf("|  __/|  _  | | | | |   | | | |\n");
	printf("| |   | | | |_| |_| |___\\ \\_/ /\n");
	printf("\\_|   \\_| |_/\\___/\\_____/\\___/ \n\n");
	printf("\033[0m");
}

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

void	creat_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_create(&data->thr[i], NULL, rootine, data->phil);
		data->phil = data->phil->next;
		pthread_detach(data->thr[i]);
		i++;
	}
	check_death(data->phil);
}

int	fill_data(t_data *data, int ac, char **av)
{
	data->optional = 0;
	data->philo_nb = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
	{
		data->optional = 1;
		data->philo_must_eat = ft_atoi(av[4]);
		if (data->philo_must_eat <= 0)
			return (1);
	}
	if (data->philo_nb <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (1);
	return (0);
}
