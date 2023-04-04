/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:56:53 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/04 00:39:35 by ohaimad          ###   ########.fr       */
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
#include <sys/time.h>

struct  s_data;

typedef struct s_list
{
    struct s_list *next;
    int id;
    long long start_time;
    pthread_mutex_t fork;
    struct s_data *data;
}   t_list;

typedef struct s_data
{
    t_list *phil;
    int		signe;
	int		res;
	int		is;
    pthread_mutex_t p;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long philo_nb;
    long philo_must_eat;
    long long start_time;
    pthread_t thr[1000];
}   t_data;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
int	    ft_lstsize(t_list *lst);
t_list	*ft_lstnew(int id, t_data *data);
void	ft_lstclear(t_list **lst);
int	    ft_atoi(char *str);
t_list	*ft_lst_last(t_list *lst);
void    philos(t_data *data, int id);
void	*printing(void *p);
void	philo_pro_max(t_data *data);
int	    fill_data(t_data *data, int ac, char **av);
long long current_time_ms();
#endif