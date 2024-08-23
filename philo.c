/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:40 by monachit          #+#    #+#             */
/*   Updated: 2024/08/23 15:52:41 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *arg)
{
	t_philo	*philo;
	t_philo	*philo2;

	philo = (t_philo *)arg;
	philo2 = philo;
	while (!check_minor(philo2))
	{
		if (time_now() - philo2->first_eat >= philo2->time_to_die)
		{
			pthread_mutex_lock(&philo2->minor->mtx_print);
			printf("%zu %zu is dead\n", time_now() - philo2->first_eat,
				philo2->id);
			philo2->minor->flag = 1;
			pthread_mutex_unlock(&philo2->minor->mtx_print);
		}
		philo2 = philo2->next;
		if (philo2 == NULL)
			philo2 = philo;
	}
	return (NULL);
}

void	ft_init_monitor(t_minor **monitor, int ac, char **av)
{
	int	i;

	i = 0;
	(*monitor)->timef = time_now();
	(*monitor)->flag = 0;
	if (ac == 6)
		(*monitor)->meals = ft_atoi(av[5]);
	else
		(*monitor)->meals = -1;
	(*monitor)->threads = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	pthread_mutex_init(&(*monitor)->mtx_print, NULL);
	pthread_mutex_init(&(*monitor)->mtx_last_eat, NULL);
	pthread_mutex_init(&(*monitor)->mtx_philo_done, NULL);
	pthread_mutex_init(&(*monitor)->mtx_flag, NULL);
}

void	ft_philo(t_philo **philo, t_minor **monitor, char **av)
{
	t_philo		*copy;
	pthread_t	l7aday;
	pthread_mutex_t *forks;
	int			i;

	i = 0;
	forks =  malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	while (i <= ft_atoi(av[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	while (i < ft_atoi(av[1]))
	{
		ft_lstadd_back1(philo, ft_inisialize_philo(av, i, monitor, forks));
		i++;
	}
	copy = *philo;
	i = 0;
	while (copy)
	{
		pthread_create(&copy->minor->threads[i], NULL, ft_fork, (void *)copy);
		copy = copy->next;
	}
	copy = *philo;
	pthread_create(&l7aday, NULL, ft_monitor, (void *)copy);
	while (copy)
	{
		pthread_join(copy->minor->threads[i], NULL);
		copy = copy->next;
	}
	pthread_join(l7aday, NULL);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_minor	*monitor;

	philo = NULL;
	if (ac != 5 && ac != 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (check_args(ac, av))
		return (printf("Error: wrong arguments\n"), 1);
	monitor = (t_minor *)malloc(sizeof(t_minor));
	if (!monitor)
		return (1);
	ft_init_monitor(&monitor, ac, av);
	ft_philo(&philo, &monitor, av);
	return (0);
}
