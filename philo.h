/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:54 by monachit          #+#    #+#             */
/*   Updated: 2024/08/20 18:49:21 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"



typedef struct t_minor
{
	pthread_mutex_t			mtx_print;
	pthread_mutex_t			mtx_last_eat;
	pthread_mutex_t			mtx_philo_done;
	pthread_mutex_t			mtx_flag;
    pthread_t   *threads;
    pthread_mutex_t *forks;
    size_t timef;
    int flag;
}              t_minor;



typedef struct t_philo
{
    size_t id;
    size_t num_philo;
    size_t first_eat;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t  meals;
    t_minor *minor;
    struct t_philo *next;
    
}               t_philo;

 

void ft_lstadd_back1(t_philo **philo, t_philo *new);
int check_args(int ac, char **av);
t_philo    *ft_inisialize_philo(char **av, size_t numbe, t_minor **monitor,  int ac);
size_t    time_now();
void    ft_update_last_eat(t_philo **philo);
void    ft_printf(char *str, t_philo *philo);
size_t    time_now();
int check_minor(t_philo *philo);
void	ft_eat(t_philo *group);
void	ft_sleep(t_philo *group);

# endif