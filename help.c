/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:29:36 by mnachit           #+#    #+#             */
/*   Updated: 2024/09/03 11:41:26 by mnachit          ###   ########.fr       */
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
	printf("%zu %zu %s\n", time_now() - philo->minor->timef, philo->id,
		str);
}

void	ft_update_last_eat(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->eat_mutex);
	(*philo)->first_eat = time_now();
	pthread_mutex_unlock(&(*philo)->eat_mutex);
}

void	ft_sleep(size_t time)
{
	size_t	deff;

	deff = time_now();
	while (1)
	{
		if (time_now() - deff >= time)
			break ;
		usleep(50);
	}
}

void	*ft_monitor(void *arg)
{
	t_philo	*philo;
	t_philo	*philo2;
	int		time;

	time = 0;
	philo = (t_philo *)arg;
	philo2 = philo;
	while (!check_minor(philo2))
	{
		pthread_mutex_lock(&philo2->eat_mutex);
		if (time_now() - philo2->first_eat >= philo2->time_to_die)
		{
			pthread_mutex_lock(&philo2->minor->check_died);
			time = time_now() - philo->minor->timef;
			philo2->minor->flag = 1;
			pthread_mutex_unlock(&philo2->minor->check_died);
			usleep(1000);
			printf("%d %zu  is died\n", time, philo2->id);
		}
		pthread_mutex_unlock(&philo2->eat_mutex);
		philo2 = philo2->next;
		if (philo2 == NULL)
			philo2 = philo;
	}
	return (NULL);
}
