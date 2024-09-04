/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:15:19 by monachit          #+#    #+#             */
/*   Updated: 2024/09/03 11:35:16 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_atoi(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (check_atoi(av, ac))
		return (1);
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
	return (0);
}

t_philo	*ft_inisialize_philo(char **av, size_t number, t_minor **monitor)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	pthread_mutex_init(&philo->eat_mutex, NULL);
	philo->minor = *monitor;
	philo->next = NULL;
	philo->id = number + 1;
	philo->first_eat = time_now();
	philo->num_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (philo->num_philo == 1)
	{
		printf("0 philo 1 has taken a fork\n");
		ft_sleep(philo->time_to_die);
		printf("%zu 1 dead\n", philo->time_to_die);
		return (NULL);
	}
	return (philo);
}
