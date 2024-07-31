/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:54 by monachit          #+#    #+#             */
/*   Updated: 2024/07/31 12:46:22 by mnachit          ###   ########.fr       */
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

# define NUM_PHILOSOPHERS 5


typedef struct t_minor
{
    pthread_mutex_t *print;
    int flag;
}              t_minor;
typedef struct t_philo
{
    int id;
    int num_philo;
    int first_eat;
    int last_eat;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    t_minor *minor;
    pthread_mutex_t *forks;
    struct t_philo *next;
    
}               t_philo;

 

void ft_lstadd_back1(t_philo **philo, t_philo *new);
int check_args(int ac, char **av);
t_philo    *ft_inisialize_philo(t_philo *philo, char **av, int number, pthread_mutex_t *forks, t_minor *monitor);
# endif