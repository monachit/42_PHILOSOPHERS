/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:54 by monachit          #+#    #+#             */
/*   Updated: 2024/07/17 17:32:47 by monachit         ###   ########.fr       */
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


typedef struct t_philo
{
    int id;
    int num_philo;
    int last_meal;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    pthread_mutex_t *forks;
    struct t_philo *next;
}               t_philo;

 

void ft_lstadd_back1(t_philo **philo, t_philo *new);
int check_args(int ac, char **av);
t_philo    *ft_inisialize_philo(t_philo *philo, char **av, int number, pthread_mutex_t *forks);
# endif