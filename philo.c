/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:40 by monachit          #+#    #+#             */
/*   Updated: 2024/08/17 11:00:02 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_minor(t_philo *philo)
{
    if (philo->minor->flag == 1)
        return (1);
    return (0);
}

size_t    time_now()
{
    size_t time;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return time;
}

void    ft_printf(char *str, t_philo *philo)
{
    if (philo->minor->flag == 1)
        return ;
    printf("%zu philo %zu %s\n", time_now() - philo->minor->timef ,philo->id, str);
}

void *ft_fork(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left_fork;
    int right_fork;
    if (philo->id % 2 != 0)
        usleep(100);
    left_fork = philo->id;
    right_fork = (philo->id + 1) % philo->num_philo; 
    while (1 == 1)
    {
        ft_printf("is thinking", philo);
        pthread_mutex_lock(&philo->forks);
        ft_printf("has taken the fork", philo);
        pthread_mutex_lock(&philo->forks);
        ft_printf("has taken a fork", philo);
        ft_printf("is eating", philo);
        philo->first_eat = time_now();
        usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->forks);
        pthread_mutex_unlock(&philo->forks);
        ft_printf("is sleeping", philo);
        usleep(100);
    }
   
    return (NULL);
}

void ft_monitor(void *arg)
{
    t_philo *philo;
    t_philo *philo2;
    size_t  i;
    
    philo = (t_philo *)arg;
    philo2 = philo;
    while (!check_minor(philo2))
    {
        i = time_now();
        if (i - philo2->first_eat >= philo2->time_to_die)
        {
            printf("%zu  == %zu === %zu  philo %zu is dead\n", i, philo2->first_eat, i - philo2->first_eat, philo2->id);
            philo->minor->flag = 1;
        }
        philo2  = philo2->next;
        if (philo2 == NULL)
            philo2 = philo;
    }
}

int main(int ac, char **av)
{

    if (ac != 5 && ac != 6)
        return (printf("Error: wrong number of arguments\n"), 1);
    if (check_args(ac, av))
        return (printf("Error: wrong arguments\n"), 1);
    t_philo *philo;
    t_minor monitor;
    monitor.timef = time_now();
    monitor.flag = 0;
    int i;
    int number;

    number = 0;
    philo = NULL;
    i = ft_atoi(av[1]);
    number = 0;
    while (i != 0)
    {
        ft_lstadd_back1(&philo, ft_inisialize_philo(philo, av, number, &monitor));
        number++;
        i--;
    }
    t_philo *philo1 = philo;
    while (philo1)
    {
        pthread_create(&philo1->threads, NULL, ft_fork, (void *)philo1);
        philo1 = philo1->next;
    }
    philo1 = philo;
    while (philo1)
    {
        pthread_join(philo1->threads, NULL);
        philo1 = philo1->next;
    }
    ft_monitor(philo);
    return (0);
}


// time >>> 
// function print >> 
//  function monitor >> 
// 