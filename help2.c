/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:31:46 by mnachit           #+#    #+#             */
/*   Updated: 2024/08/23 15:51:56 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_fork(void *arg)
{
	t_philo	*philo;
	int	i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(100);
	while (!check_minor(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		ft_printf("has taken the fork", philo);
		pthread_mutex_lock(philo->right_fork);
		ft_printf("has taken a fork", philo);
		ft_printf("is eating", philo);
		ft_update_last_eat(&philo);
		ft_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_printf("is sleeping", philo);
		ft_sleep(philo);
		ft_printf("is thinking", philo);
	}
	return (NULL);
}

int	check_minor(t_philo *philo)
{
	if (philo->minor->flag == 1)
		return (1);
	return (0);
}
