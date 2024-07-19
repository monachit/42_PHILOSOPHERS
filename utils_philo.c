/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:15:19 by monachit          #+#    #+#             */
/*   Updated: 2024/07/17 17:20:51 by monachit         ###   ########.fr       */
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

t_philo    *ft_inisialize_philo(t_philo *philo, char **av, int number, pthread_mutex_t *forks)
{
    philo = malloc(sizeof(t_philo));
    philo->next = NULL;
    philo->id = number;
    philo->num_philo = ft_atoi(av[1]);
    philo->time_to_die = ft_atoi(av[2]);
    philo->time_to_eat = ft_atoi(av[3]);
    philo->time_to_sleep = ft_atoi(av[4]);
    philo->forks = forks;
    return (philo);
}
