/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:29:36 by mnachit           #+#    #+#             */
/*   Updated: 2024/08/23 15:49:52 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_now(void)
{
	size_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	ft_printf(char *str, t_philo *philo)
{
	if (check_minor(philo))
		return ;
	pthread_mutex_lock(&philo->minor->mtx_print);
	printf("%zu philo %zu %s\n", time_now() - philo->minor->timef, philo->id,
		str);
	pthread_mutex_unlock(&philo->minor->mtx_print);
}

void	ft_update_last_eat(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->minor->mtx_last_eat);
	(*philo)->first_eat = time_now();
	pthread_mutex_unlock(&(*philo)->minor->mtx_last_eat);
}

void	ft_eat(t_philo *group)
{
	size_t	deff;

	if (check_minor(group))
		return ;
	deff = time_now();
	while (time_now() - deff <= (size_t)group->time_to_eat)
	{
		usleep(5);
	}
}

void	ft_sleep(t_philo *group)
{
	size_t	deff;

	if (check_minor(group))
		return ;
	deff = time_now();
	while (time_now() - deff <= (size_t)group->time_to_sleep)
	{
		usleep(5);
	}
}
