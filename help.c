/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:31:52 by mnachit           #+#    #+#             */
/*   Updated: 2024/08/20 18:33:26 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_minor(t_philo *philo)
{
    
    if (philo->minor->flag == 1)
    {
        // printf("=====> %d minor addr %p %d\n", philo->id,  philo->minor, philo->minor->flag);
        return (1);
    }
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
    if (check_minor(philo))
        return ;
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

    if (check_minor(group))
        return ;
	deff = time_now();
	while (time_now() - deff <= (unsigned long long )group->time_to_eat)
    {
		usleep(500);
	}
}

void	ft_sleep(t_philo *group)
{
	unsigned long long	deff;

    if (check_minor(group))
        return ;
	deff = time_now();
	while (time_now() - deff <= (unsigned long long )group->time_to_sleep)
	{
		usleep(500);
	}
}