/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:06:15 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/09 06:58:55 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

t_list	*ft_lstnew(int id, t_data *data)
{
	t_list			*philo;
	pthread_mutex_t	fork;

	pthread_mutex_init(&fork, NULL);
	philo = malloc(sizeof(t_list));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->data = data;
	philo->start_time = current_time_ms();
	philo->last_meal = current_time_ms();
	philo->fork = fork;
	philo->next = NULL;
	return (philo);
}
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (!new)
		return ;
	head = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*new;

	if (!lst)
		return ;
	while (*lst)
	{
		new = (*lst)->next;
		free(*lst);
		*lst = new;
	}
	*lst = NULL;
}

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
