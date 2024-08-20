/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:40 by monachit          #+#    #+#             */
/*   Updated: 2024/08/20 18:52:10 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void *ft_fork(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left_fork = philo->id ;
    int  right_fork = (philo->id + 1) % philo->num_philo;
    int sum = 0;
    if (philo->id % 2 != 0)
        usleep(1000);
    while (!check_minor(philo) && (philo->meals == -1 || philo->meals != sum))
    {
        pthread_mutex_lock(&philo->minor->forks[left_fork]);
        ft_printf("has taken the fork", philo);
        pthread_mutex_lock(&philo->minor->forks[right_fork]);
        ft_printf("has taken a fork", philo);
        ft_printf("is eating", philo);
        ft_update_last_eat(&philo);
        ft_eat(philo);
        pthread_mutex_unlock(&philo->minor->forks[left_fork]);
        ft_printf("has put the fork", philo);
        pthread_mutex_unlock(&philo->minor->forks[right_fork]);
        ft_printf("has put the fork", philo);
        ft_printf("is sleeping", philo);
        ft_sleep(philo);
        ft_printf("is thinking", philo);
        sum++;
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
            pthread_mutex_lock(&philo2->minor->mtx_print);
            printf("%zu %d is dead\n", time_now() - philo2->first_eat, philo2->id);
            philo2->minor->flag = 1;
            pthread_mutex_unlock(&philo2->minor->mtx_print);

        }
        philo2  = philo2->next;
        if (philo2 == NULL)
            philo2 = philo;
    }
    // printf("minor sla\n");
    return (NULL);
}

void    ft_init(t_minor *monitor, t_philo **philo, char **av, int ac)
{
    int number;
    
    monitor->timef = time_now();
    monitor->flag = 0;
    monitor->threads = malloc(sizeof(pthread_t) *  ft_atoi(av[1]));
    monitor->forks = malloc(sizeof(pthread_mutex_t) *  ft_atoi(av[1]));
    pthread_mutex_init(&monitor->mtx_print, NULL);
	pthread_mutex_init(&monitor->mtx_last_eat, NULL);
	pthread_mutex_init(&monitor->mtx_philo_done, NULL);
	pthread_mutex_init(&monitor->mtx_flag, NULL);
    number = 0;
    while (number != ft_atoi(av[1]))
    {
        pthread_mutex_init(&monitor->forks[number], NULL);
        number++;
    }
    number = 0;
    while (number != ft_atoi(av[1]))
    {   
        t_philo *new_philo = ft_inisialize_philo(av, number, &monitor, ac);
         ft_lstadd_back1(philo, new_philo);
         number++;
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
    pthread_t   l7aday;
    philo = NULL;
    ft_init(&monitor, &philo, av, ac);
    int i = 0;
    t_philo *philo1 = philo;
    while (philo1)
    {
        pthread_create(&philo->minor->threads[i], NULL, ft_fork, (void *)philo1);
        i++;
        philo1 = philo1->next;
    }
    philo1 = philo;
    pthread_create(&l7aday, NULL, ft_monitor, (void *)philo);
    while (philo1)
    {
        pthread_join(philo1->minor->threads[i], NULL);
        i++;
        philo1 = philo1->next;
    }
    pthread_join(l7aday, NULL);
    return (0);
}
