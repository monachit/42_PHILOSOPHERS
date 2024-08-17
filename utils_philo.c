/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:15:19 by monachit          #+#    #+#             */
/*   Updated: 2024/08/17 10:48:53 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(int ac, char **av)
{
    int i;
    int j;
    
    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
    while (i < ac)
    {
        if (av[i][0] == '-')
            return (1);
        i++;
    }
    return (0);
}

t_philo    *ft_inisialize_philo(t_philo *philo, char **av, size_t number, t_minor *monitor)
{
    philo = malloc(sizeof(t_philo));
    philo->minor = monitor;
    philo->next = NULL;
    philo->id = number;
    philo->first_eat = time_now();
    philo->last_eat = 0;
    philo->num_philo = ft_atoi(av[1]);
    philo->time_to_die = ft_atoi(av[2]);
    philo->time_to_eat = ft_atoi(av[3]);
    philo->time_to_sleep = ft_atoi(av[4]);
    pthread_mutex_init(&philo->forks, NULL);
    return (philo);
}
