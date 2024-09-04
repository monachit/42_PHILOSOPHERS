/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:54 by monachit          #+#    #+#             */
/*   Updated: 2024/09/02 13:28:43 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_minor
{
	pthread_mutex_t	mtx_philo_done;
	pthread_mutex_t	check_died;
	size_t			timef;
	int				flag;
}					t_minor;

typedef struct t_philo
{
	size_t			id;
	size_t			num_philo;
	size_t			first_eat;
	size_t			time_to_die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_mutex;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meals;
	t_minor			*minor;
	struct t_philo	*next;

}					t_philo;

void				ft_lstadd_back1(t_philo **philo, t_philo *new);
int					check_args(int ac, char **av);
t_philo				*ft_inisialize_philo(char **av, size_t n, t_minor **m);
void				ft_update_last_eat(t_philo **philo);
void				ft_printf(char *str, t_philo *philo);
size_t				time_now(void);
int					check_minor(t_philo *philo);
void				*ft_monitor(void *arg);
void				ft_sleep(size_t time);
void				*ft_fork(void *arg);
void				ft_free_forks(t_philo **philo);
int					ft_atoi(char *str);
int					return_value(char **av, int ac);

#endif