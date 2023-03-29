/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:09:15 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/24 11:26:15 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_real_init_meta(t_glob *meta, int ac, char **av)
{
	int	i;
	int	n_phil;

	i = -1;
	n_phil = ft_utoi(av[PHIL]);
	if (ac == 6)
		while (++i < n_phil)
			meta->times[i] = ft_utoi(av[TIMES]);
	else
		while (++i < n_phil)
			meta->times[i] = -1;
	meta->n_phil = n_phil;
	meta->time_die = ft_utoi(av[DIE]);
	meta->dead = 0;
	meta->last_meal = (time_t *) malloc(n_phil * sizeof(time_t));
	meta->start_time = get_time();
	if (!meta->last_meal)
		return (1);
	i = -1;
	while (++i < n_phil)
		meta->last_meal[i] = meta->start_time;
	return (0);
}

int	ft_init_meta_philo(t_glob *meta, t_phil *philo, int ac, char **av)
{
	int	i;
	int	n_phil;

	n_phil = ft_utoi(av[PHIL]);
	meta->times = (int *) malloc(n_phil * sizeof(int));
	if (!meta->times)
		return (1);
	if (ft_real_init_meta(meta, ac, av))
		return (2);
	i = 0;
	while (i < n_phil)
	{
		philo[i].phid = i;
		philo[i].next_fork = (i + 1);// % n_phil;
		philo[i].meta = meta;
		philo[i].start_time = meta->start_time;
		philo[i].time_eat = ft_utoi(av[EAT]);
		philo[i].time_sleep = ft_utoi(av[SLEEP]);
		i++;
	}
	return (0);
}

int	ft_init_mutex(t_glob *meta, int n_phil)
{
	int	i;

	pthread_mutex_init(&meta->print, NULL);
	meta->fork = malloc((n_phil + 1) * sizeof(pthread_mutex_t));
	if (!meta->fork)
		return (1);
	i = -1;
	while (++i < n_phil)
		pthread_mutex_init(&meta->fork[i], NULL);
	meta->fork[i] = meta->fork[0];
	return (0);
}

void	ft_start_dinner(t_glob *meta, t_phil *philo, int n_phil)
{
	int			i;
	pthread_t	monitor;

	meta->phth = (pthread_t *) malloc(n_phil * sizeof(pthread_t));
	pthread_create(&monitor, NULL, (void *) monitor_death, meta);
	if (meta->n_phil == 1)
	{
		pthread_create(&meta->phth[0], NULL, (void *) print_fork, &philo[0]);
		pthread_join(meta->phth[0], NULL);
	}
	else
	{
		i = -1;
		while (++i < n_phil)
		{
			pthread_create(&meta->phth[i], NULL,
				(void *) philo_life, &philo[i]);
		}
		i = -1;
		while (++i < n_phil)
			pthread_join(meta->phth[i], NULL);
	}
	pthread_join(monitor, NULL);
}
