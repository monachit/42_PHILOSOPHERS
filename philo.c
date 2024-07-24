/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:40 by monachit          #+#    #+#             */
/*   Updated: 2024/07/24 17:42:28 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *ft_fork(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left_fork;
    int right_fork;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (philo->id % 2 == 0)
        usleep(1000);
    left_fork = philo->id;
    right_fork = (philo->id + 1) % philo->num_philo;
    while (1)
    {
        printf("philo %d is thinking\n", philo->id);
        pthread_mutex_lock(&philo->forks[left_fork]);
        pthread_mutex_lock(&philo->forks[right_fork]);
        printf("philo %d has taken a fork\n", philo->id);
        printf("philo %d has taken a fork\n", philo->id);
        printf("philo %d is eating\n", philo->id);
        usleep(philo->time_to_eat * 10000);
        pthread_mutex_unlock(&philo->forks[left_fork]);
        pthread_mutex_unlock(&philo->forks[right_fork]);
        usleep(philo->time_to_sleep * 10000);
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
    pthread_t thread[ft_atoi(av[1])];
    pthread_mutex_t forks[ft_atoi(av[1])];
    int i;
    int number;

    number = 0;
    philo = NULL;
    i = ft_atoi(av[1]);
    while (number < i)
    {
        pthread_mutex_init(&forks[number], NULL);
        number++;
    }
    number = 0;
    while (i != 0)
    {
        ft_lstadd_back1(&philo, ft_inisialize_philo(philo, av, number, forks));
        number++;
        i--;
    }
    t_philo *philo1 = philo;
    while (philo1)
    {
        pthread_create(&thread[philo1->id], NULL, ft_fork, (void *)philo1);
        philo1 = philo1->next;
    }
    philo1 = philo;
    while (philo1)
    {
        pthread_join(thread[philo1->id], NULL);
        philo1 = philo1->next;
    }
    return (0);
}