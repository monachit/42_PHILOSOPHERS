/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:31:46 by mnachit           #+#    #+#             */
/*   Updated: 2024/09/03 10:52:39 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eat(t_philo **philo)
{
	ft_printf("is eating", *philo);
	ft_update_last_eat(philo);
	ft_sleep((*philo)->time_to_eat);
}

void	is_sleep1(t_philo **philo)
{
	ft_printf("is sleeping", *philo);
	ft_sleep((*philo)->time_to_sleep);
	ft_printf("is thinking", *philo);
}

void	ft_take_theforks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_printf("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		ft_printf("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_printf("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		ft_printf("has taken a fork", philo);
	}
}

void	*ft_fork(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_minor(philo) && philo->meals != 0)
	{
		ft_take_theforks(philo);
		is_eat(&philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		is_sleep1(&philo);
		usleep(200);
		philo->meals--;
	}
	pthread_mutex_lock(&philo->minor->check_died);
	philo->minor->flag = 1;
	pthread_mutex_unlock(&philo->minor->check_died);
	return (NULL);
}

int	check_minor(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->minor->check_died);
	result = philo->minor->flag;
	pthread_mutex_unlock(&philo->minor->check_died);
	return (result);
}
