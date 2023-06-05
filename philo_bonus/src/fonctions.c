/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:46:07 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/05 19:38:50 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher_bonus.h"

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
	int		i;
	int		k;
	sem_t	*my_semaphore;
	sem_t	*my_print;

	k = id;
	data->phil = NULL;
	i = 1;
	while (id-- >= 1)
		ft_lstadd_back(&data->phil, ft_lstnew(i++, data));
	ft_lst_last(data->phil)->next = data->phil;
	sem_unlink("my_semaphore");
	my_semaphore = sem_open("my_semaphore", O_CREAT, 0644, k);
	sem_unlink("my_print");
	my_print = sem_open("my_print", O_CREAT, 0644, 1);
	while (k--)
	{
		data->phil->forks = my_semaphore;
		data->phil->my_print = my_print;
		data->phil = data->phil->next;
	}
}
// Mutex : mutual exclusion; a mutex is a lock that we can lock and unlock to protect a section of code from being accessed by multiple threads at once.
void	creat_philos(t_data *data)
{
	int		i;
	t_list	*phil;
	int		status;

	i = 0;
	phil = data->phil;
	while (i < data->philo_nb)
	{
		phil->pid = fork();
		if (phil->pid < 0)
			printf("Error\n");
		else if (phil->pid == 0)
		{
			// This is the child process representing philosopher i
			rootine(phil);
			exit(0);
		}
		// else
		// {
		// 	kill(pid, SIGKILL);
		// }
		phil = phil->next;
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == 0)
		{
			phil = data->phil;
			i = 0;
			while (i < data->philo_nb)
			{
				kill(phil->pid, SIGKILL);
				i++;
				phil = phil->next;
			}
			exit(0);
		}
		// }
		phil = phil->next;
		i++;
	}
	exit(0);
}

// while (wait(NULL) > 0);
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
