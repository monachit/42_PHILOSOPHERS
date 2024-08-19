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
    pthread_mutex_lock(&philo->minor->mtx_print);
    printf("%zu philo %zu %s\n", time_now() - philo->minor->timef ,philo->id, str);
    pthread_mutex_unlock(&philo->minor->mtx_print);
}

void    ft_update_last_eat(t_philo **philo)
{
    pthread_mutex_lock(&(*philo)->minor->mtx_last_eat);
    (*philo)->first_eat = time_now();
    pthread_mutex_unlock(&(*philo)->minor->mtx_last_eat);
}

void	ft_eat(t_philo *group)
{
	unsigned long long	deff;

	deff = time_now();
	while (time_now() - deff <= (unsigned long long )group->time_to_eat)
    {
		usleep(500);
	}
}

void	ft_sleep(t_philo *group)
{
	unsigned long long	deff;

	deff = time_now();
	while (time_now() - deff <= (unsigned long long )group->time_to_sleep)
	{
		usleep(500);
	}
}

void *ft_fork(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left_fork = philo->id ;
    int  right_fork = (philo->id + 1) % philo->num_philo; 
    if (philo->id % 2 != 0)
        usleep(100);
    while (!check_minor(philo))
    {
        ft_printf("has taken the fork", philo);
        pthread_mutex_lock(&philo->minor->forks[left_fork]);
        ft_printf("has taken a fork", philo);
        pthread_mutex_lock(&philo->minor->forks[right_fork]);
        ft_printf("is eating", philo);
        ft_update_last_eat(&philo);
        ft_eat(philo);
        pthread_mutex_unlock(&philo->minor->forks[left_fork]);
        pthread_mutex_unlock(&philo->minor->forks[right_fork]);
        ft_printf("is sleeping", philo);
        ft_sleep(philo);
        ft_printf("is thinking", philo);
    }
   
    return (NULL);
}

void *ft_monitor(void *arg)
{
    t_philo *philo;
    t_philo *philo2;
    
    philo = (t_philo *)arg;
    philo2 = philo;
    while (!check_minor(philo2))
    {
        if (time_now() - philo2->first_eat >= philo2->time_to_die)
        {
            pthread_mutex_lock(&philo->minor->mtx_print);
            printf("%zu %d is dead\n", time_now() - philo2->first_eat, philo2->id);
            philo->minor->flag = 1;
        }
        philo2  = philo2->next;
        if (philo2 == NULL)
            philo2 = philo;
    }
    return (NULL);
}

int main(int ac, char **av)
{

    if (ac != 5 && ac != 6)
        return (printf("Error: wrong number of arguments\n"), 1);
    if (check_args(ac, av))
        return (printf("Error: wrong arguments\n"), 1);
    t_philo *philo;
    t_minor monitor;
    pthread_t   l7aday;
    monitor.timef = time_now();
    monitor.flag = 0;
    monitor.threads = malloc(sizeof(pthread_t) *  ft_atoi(av[1]));
    monitor.forks = malloc(sizeof(pthread_mutex_t) *  ft_atoi(av[1]));
    pthread_mutex_init(&monitor.mtx_print, NULL);
	pthread_mutex_init(&monitor.mtx_last_eat, NULL);
	pthread_mutex_init(&monitor.mtx_philo_done, NULL);
	pthread_mutex_init(&monitor.mtx_flag, NULL);
    int i;
    int number;
    number = 0;
    while (number != ft_atoi(av[1]))
    {
        pthread_mutex_init(&monitor.forks[number], NULL);
        number++;
    }
    philo = NULL;
    i = ft_atoi(av[1]);
    number = 0;
    while (i != 0)
    {   
        t_philo *new_philo = ft_inisialize_philo(av, number, &monitor);
         if (!new_philo)
             return (printf("Error: failed to allocate memory for philosopher\n"), 1);
         ft_lstadd_back1(&philo, new_philo);
         number++;
         i--;
    }
    t_philo *philo1 = philo;
    while (philo1)
    {
        pthread_create(&philo->minor->threads[i], NULL, ft_fork, (void *)philo1);
        philo1 = philo1->next;
    }
    philo1 = philo;
    pthread_create(&l7aday, NULL, &ft_monitor, (void *)philo);
    while (philo1)
    {
        pthread_join(philo1->minor->threads[i], NULL);
        philo1 = philo1->next;
    }
    pthread_join(l7aday, NULL);
    return (0);
}