/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:40 by monachit          #+#    #+#             */
/*   Updated: 2024/09/03 11:36:56 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_monitor(t_minor **monitor)
{
	int	i;

	i = 0;
	(*monitor)->timef = time_now();
	(*monitor)->flag = 0;
	pthread_mutex_init(&(*monitor)->mtx_philo_done, NULL);
	pthread_mutex_init(&(*monitor)->check_died, NULL);
}

void	norm2(t_philo **philo, pthread_mutex_t *forks, int ac, int i)
{
	(*philo)->left_fork = &forks[i];
	(*philo)->right_fork = &forks[(i + 1) % (*philo)->num_philo];
	(*philo)->meals = ac;
}

pthread_mutex_t	*ft_norm(t_philo **p, t_minor **m, char **av, int ac)
{
	pthread_mutex_t	*forks;
	int				i;
	t_philo			*new;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		new = ft_inisialize_philo(av, i, m);
		if (!new)
			return (NULL);
		norm2(&new, forks, ac, i);
		ft_lstadd_back1(p, new);
		i++;
	}
	return (forks);
}

void	ft_philo(t_philo **philo, t_minor **monitor, char **av, int ac)
{
	t_philo			*copy;
	pthread_t		l7aday;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	forks = ft_norm(philo, monitor, av, ac);
	if (!philo || !forks)
		return ;
	copy = *philo;
	while (copy)
	{
		pthread_create(&threads[i++], NULL, ft_fork, (void *)copy);
		copy = copy->next;
	}
	i = 0;
	pthread_create(&l7aday, NULL, ft_monitor, (void *)*philo);
	while (i < ft_atoi(av[1]))
		pthread_join(threads[i++], NULL);
	pthread_join(l7aday, NULL);
	ft_free_forks(philo);
	free(threads);
	free(forks);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_minor	*monitor;
	size_t	po;
	t_philo	*new;

	philo = NULL;
	if (ac != 5 && ac != 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (check_args(ac, av))
		return (printf("Error: wrong arguments\n"), 1);
	monitor = (t_minor *)malloc(sizeof(t_minor));
	if (!monitor)
		return (1);
	po = return_value(av, ac);
	ft_init_monitor(&monitor);
	ft_philo(&philo, &monitor, av, po);
	new = philo;
	while (new)
	{
		philo = new;
		new = new->next;
		free(philo);
	}
	free(monitor);
	return (0);
}
