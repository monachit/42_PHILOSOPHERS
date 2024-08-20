/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:15:19 by monachit          #+#    #+#             */
/*   Updated: 2024/08/20 18:53:31 by mnachit          ###   ########.fr       */
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

t_philo    *ft_inisialize_philo(char **av, size_t number, t_minor **monitor, int ac)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    if (!philo) // Check if malloc failed
        return (NULL);
    philo->minor = *monitor;
    philo->next = NULL;
    philo->id = number;
    philo->first_eat = time_now();
    philo->num_philo = ft_atoi(av[1]);
    philo->time_to_die = ft_atoi(av[2]);
    philo->time_to_eat = ft_atoi(av[3]);
    philo->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        philo->meals = ft_atoi(av[5]);
    else
        philo->meals = -1;
    return (philo);
}
