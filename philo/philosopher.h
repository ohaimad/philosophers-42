/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:56:53 by ohaimad           #+#    #+#             */
/*   Updated: 2023/03/28 00:22:49 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>


typedef struct s_data
{
    long time_to_die; 
    long time_to_eat; 
    long time_to_sleep;
    long philo_nb;
    long must_eat;
    int		signe;
	int		res;
    
}   t_data;

typedef struct s_list
{
    struct s_list *next;
    int id;
    pthread_mutex_t fork;
    t_data data;
}   t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
int	    ft_lstsize(t_list *lst);
t_list	*ft_lstnew(int id);
void	ft_lstclear(t_list **lst);
int	    ft_atoi(char *str);

#endif