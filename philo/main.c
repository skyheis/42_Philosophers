/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:31:30 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 16:29:48 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_solo(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	printf("%-7li %2i has taken a fork 🍴\n",
		philo->start_time, philo->phid);
	pthread_mutex_unlock(&philo->meta->print);
}

void	philo_life(t_phil *philo)
{
	if (philo->phid % 2)
		ft_msleep(15);
	pthread_mutex_lock(&philo->meta->print);
	while (!philo->meta->dead)
	{
		pthread_mutex_unlock(&philo->meta->print);
		pthread_mutex_lock(&philo->meta->fork[philo->phid]);
		print_fork(philo);
		pthread_mutex_lock(&philo->meta->fork[philo->next_fork]);
		print_fork(philo);
		pthread_mutex_lock(&philo->meta->print);
		if (philo->meta->times[philo->phid] > 0)
			philo->meta->times[philo->phid] -= 1;
		philo->meta->last_meal[philo->phid] = get_time();
		pthread_mutex_unlock(&philo->meta->print);
		print_eat(philo);
		ft_msleep(philo->time_eat);
		pthread_mutex_unlock(&philo->meta->fork[philo->phid]);
		pthread_mutex_unlock(&philo->meta->fork[philo->next_fork]);
		print_sleeping(philo);
		ft_msleep(philo->time_sleep);
		print_think(philo);
		pthread_mutex_lock(&philo->meta->print);
	}
	pthread_mutex_unlock(&philo->meta->print);
}

int	monitor_checks(t_glob *meta, int *all_ate, int i)
{
	pthread_mutex_lock(&meta->print);
	if (get_time() - meta->last_meal[i] >= meta->time_die)
	{
		meta->dead = 1;
		printf("%-7li %2i is dead 💀\n",
			get_time() - meta->start_time, i + 1);
		pthread_mutex_unlock(&meta->print);
		return (1);
	}
	else
		pthread_mutex_unlock(&meta->print);
	pthread_mutex_lock(&meta->print);
	if (meta->times[i] == 0)
		*all_ate -= 1;
	pthread_mutex_unlock(&meta->print);
	return (0);
}

void	monitor_death(t_glob *meta)
{
	int	i;
	int	n_phil;
	int	all_ate;

	n_phil = meta->n_phil;
	all_ate = n_phil;
	while (1)
	{
		i = -1;
		ft_msleep(1);
		while (++i < n_phil)
		{
			if (monitor_checks(meta, &all_ate, i))
				return ;
		}
		if (all_ate == 0)
		{
			pthread_mutex_lock(&meta->print);
			meta->dead = 1;
			pthread_mutex_unlock(&meta->print);
			return ;
		}
		all_ate = n_phil;
	}
}

int	main(int ac, char **av)
{
	t_phil	*philo;
	t_glob	*meta;
	int		n_phil;

	if (ac < 5 || ac > 6)
		return (42);
	n_phil = ft_utoi(av[PHIL]);
	if (n_phil < 1)
		return (printf("No philo no game 💀\n"));
	philo = (t_phil *) malloc(n_phil * sizeof(t_phil));
	meta = (t_glob *) malloc(sizeof(t_glob));
	if (!meta || !philo)
		return (ft_free_philo(&philo, &meta, n_phil));
	if (ft_init_meta_philo(meta, philo, ac, av))
		return (ft_free_philo(&philo, &meta, n_phil));
	if (ft_init_mutex(meta, n_phil))
		return (ft_free_philo(&philo, &meta, n_phil));
	ft_start_dinner(meta, philo, n_phil);
	ft_free_philo(&philo, &meta, n_phil);
	return (0);
}
