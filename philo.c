/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:40 by monachit          #+#    #+#             */
/*   Updated: 2024/07/27 10:35:06 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_dead(t_philo *philo, int time, int f, int l)
{
    static int i = 0;

    i += (f / 10000) - (l / 10000);
    if (i > philo->time_to_die)
        return (1);
    return (0);
    
}


void *ft_fork(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left_fork;
    int right_fork;
    struct timeval tv;
    int time;

    time = 0;
    if (philo->id % 2 != 0)
        usleep(1000);
    left_fork = philo->id;
    right_fork = (philo->id + 1) % philo->num_philo;
    while (1)
    {
        printf("philo %d is thinking\n", philo->id);
        pthread_mutex_lock(&philo->forks[left_fork]);
        pthread_mutex_lock(&philo->forks[right_fork]);
        gettimeofday(&tv, NULL);
        philo->first_eat = tv.tv_usec;
        printf("1 == philo %d has taken a fork\n", philo->id);
        printf("2 == philo %d has taken a fork\n", philo->id);
        printf("philo %d is eating\n", philo->id);
        usleep(philo->time_to_eat * 10000);
        gettimeofday(&tv, NULL);
        philo->last_eat = tv.tv_usec;
        time++;
        if (time == philo->id)
            time = 0;
        if (check_dead(philo, time, philo->first_eat, philo->last_eat) == 1)
        {
            pthread_mutex_unlock(&philo->forks[left_fork]);
            pthread_mutex_unlock(&philo->forks[right_fork]);
            printf("philo %d is dead\n", philo->id);
            return (NULL);
        }
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