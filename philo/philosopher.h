/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:56:53 by ohaimad           #+#    #+#             */
/*   Updated: 2023/05/20 17:27:48 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <ctype.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_data;

typedef struct s_list
{
	struct s_list	*next;
	int				id;
	int				nb_eat;
	long long		start_time;
	long long		last_meal;
	pthread_mutex_t	fork;
	struct s_data	*data;
}					t_list;

typedef struct s_data
{
	int				res;
	int				is;
	int				optional;
	int				check;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philo_nb;
	long			philo_must_eat;
	t_list			*phil;
	pthread_mutex_t	p;
	pthread_mutex_t	luck;
	pthread_mutex_t	eat;
	pthread_t		thr[1000];
}					t_data;

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(int id, t_data *data);
void				ft_lstclear(t_list **lst);
int					ft_atoi(char *str);
t_list				*ft_lst_last(t_list *lst);
void				philos(t_data *data, int id);
void				*rootine(void *p);
void				creat_philos(t_data *data);
int					fill_data(t_data *data, int ac, char **av);
long long			current_time_ms(void);
void				ft_design(void);
void				check_death(t_list *phil);
int					check_digit(int ac, char **av);
void				ft_destroy(t_list *phil);
void				my_usleep(long long ms);
void				check_optional(t_list *phil);

#endif