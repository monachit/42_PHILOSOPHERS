/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:29:18 by monachit          #+#    #+#             */
/*   Updated: 2024/07/13 17:31:32 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstadd_back1(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if (!*philo)
	{
		*philo = new;
		return ;
	}
	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_free_forks(t_philo **philo)
{
	t_philo	*tmp;

	tmp = *philo;
	while (tmp)
	{
		pthread_mutex_destroy(tmp->left_fork);
		pthread_mutex_destroy(&tmp->eat_mutex);
		tmp = tmp->next;
	}
	pthread_mutex_destroy(&(*philo)->minor->mtx_philo_done);
	pthread_mutex_destroy(&(*philo)->minor->check_died);
}

int	ft_atoi(char *str)
{
	long	n_p;
	long	r;
	int		i;

	i = 0;
	n_p = 1;
	r = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n_p = n_p * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	r *= n_p;
	if (r > 2147483647 || r < -2147483648)
		return (-1);
	return (r);
}

int	return_value(char **av, int ac)
{
	size_t	po;

	if (ac == 6)
		po = ft_atoi(av[5]);
	else
		po = -1;
	return (po);
}
