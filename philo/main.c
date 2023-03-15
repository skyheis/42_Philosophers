/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:31:30 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/15 16:51:50 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	ft_init_struct(int ac, char **av, t_phil *philo)
{
	int	i;

	philo->n_phil = ft_utoi(av[1]);
	philo->time_die = ft_utoi(av[2]);
	philo->time_eat = ft_utoi(av[3]);
	philo->time_sleep = ft_utoi(av[4]);
	if (ac == 6)
	{
		philo->n_times = ft_utoi(av[5]);
		philo->times = (int *) malloc(philo->n_phil * sizeof(int));
		if (!philo->times)
			return (0);
		while (++i < philo->n_phil)
			philo->times[i] = philo->n_times;
	}
	else
		philo->n_times = -1;
	philo->phth = NULL;
	philo->fork = NULL;
	philo->times = NULL;
	return (1);
}

t_phil	*ft_init_philo(int ac, char **av)
{
	t_phil	*philo;
	int		i;

	i = 0;
	if (ft_check_args(ac, av))
		return (NULL);
	philo = (t_phil *) malloc(sizeof(t_phil));
	if (!philo)
		return (NULL);
	if (!ft_init_struct(ac, av, philo))
		return (ft_free_philo(&philo));
	philo->phth = (pthread_t *) malloc(philo->n_phil * sizeof(pthread_t));
	if (!philo->phth)
		return (ft_free_philo(&philo));
	philo->fork = (pthread_mutex_t *) malloc(philo->n_phil * sizeof(pthread_mutex_t));
	if (!philo->fork)
		return (ft_free_philo(&philo));
	while (i < philo->n_phil)
		pthread_mutex_init(&philo->fork[i++], NULL); //parentesi?
	return (philo);
}*/

/* routine should be:
 *
 * lock dead
 * enter a big loop
 *  unlock dead
 *  lock my fork (print)
 *  lock fork + 1 (print)
 *  eat (print)
 *  unlock fork + 1
 *  unlock my fork
 *  sleep and wait(print)
 *  think (print)
 *  lock dead
 * say bye
 */

void	ft_msleep(unsigned int x)
{
	usleep(x * 1000);
}

void	*philo_life(t_phil *philo)
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
		print_eat(philo);
		
		pthread_mutex_lock(&philo->meta->print);
		philo->meta->times[philo->phid] -= 1;
		philo->meta->last_meal[philo->phid] = get_time();
		pthread_mutex_unlock(&philo->meta->print);
		
		ft_msleep(philo->time_eat);
		pthread_mutex_unlock(&philo->meta->fork[philo->next_fork]);
		pthread_mutex_unlock(&philo->meta->fork[philo->phid]);
		print_sleeping(philo);
		ft_msleep(philo->time_sleep);
		print_think(philo);
		pthread_mutex_lock(&philo->meta->print);
	}
	return (NULL);
}

void	*rout_test(t_phil *philo)
{
	int i = 0;

	while (i++ < 1000)
	{
		//pthread_mutex_lock(&philo->meta->test);
		philo->meta->times[philo->phid] += 1;
		//pthread_mutex_unlock(&philo->meta->test);
	}
	print_fork(philo);
	return (NULL);
}

void	monitor_death(t_glob *meta)
{
	int	i;
	int	n_phil;

	n_phil = meta->n_phil;
	while (1)
	{
		i = -1;
		while (++i < n_phil)
		{
			pthread_mutex_lock(&meta->print);
			if (meta->last_meal[i] - meta->start_time > meta->time_die)
			{
				meta->dead = 1;
				printf("%-7li %2i is dead 💀\n",
					get_time() - meta->start_time, i + 1);
				pthread_mutex_unlock(&meta->print);
				return ;
			}
			pthread_mutex_unlock(&meta->print);
		}
	}
}

int	main(int ac, char **av)
{
	t_phil	*philo;
	t_glob	*meta;
	pthread_t	monitor;
	int		n_phil;
	int		i = 0;
//	time_t	start_time;

	if (ac != 5)
		return (42);

	n_phil = ft_utoi(av[1]);
	philo = (t_phil *) malloc(n_phil * sizeof(t_phil));
	if (!philo)
		return (1);

	//init glob
	meta = (t_glob *) malloc(sizeof(t_glob));
	if (!meta)
		return (2);
	meta->times = (int *) malloc(n_phil * sizeof(int));
	if (!meta->times)
		return (3);
	i = -1;
	if (ac == 6)
		while (++i < n_phil)
			meta->times[i] = ft_utoi(av[5]);
	else
		while (++i < n_phil)
			meta->times[i] = -1;
	meta->n_phil = n_phil;
	meta->time_die = ft_utoi(av[2]);
	meta->dead = 0;
	meta->last_meal = (time_t *) malloc(n_phil * sizeof(time_t));
	meta->start_time = get_time();
	if (!meta->last_meal)
		return (3);
	i = -1;
	while (++i < n_phil)
		meta->last_meal[i] = meta->start_time;

	i = 0;
	while (i < n_phil)
	{
		philo[i].phid = i;
		philo[i].next_fork = (i + 1) % n_phil;
		philo[i].meta = meta;
		philo[i].start_time = meta->start_time;
		philo[i].time_eat = ft_utoi(av[3]); //fix
		philo[i].time_sleep = ft_utoi(av[4]); //fix
		i++;
	}


//puo stare nell'init glob
	pthread_mutex_init(&meta->print, NULL);
	pthread_mutex_init(&meta->test, NULL);
	//meta->fork = NULL;
	meta->fork = (pthread_mutex_t *) malloc(n_phil * sizeof(pthread_mutex_t));
	if (!meta->fork)
		return (4);
	i = -1;
	while (++i < n_phil)
		pthread_mutex_init(&meta->fork[i], NULL);


	i = -1;
	meta->phth = (pthread_t *) malloc(n_phil * sizeof(pthread_t));
	pthread_create(&monitor, NULL, (void *) monitor_death, &meta);
	while (++i < n_phil)
	{
		pthread_create(&meta->phth[i], NULL, (void *) philo_life, &philo[i]);
	}
	i = -1;
	while (++i < n_phil)
	{
		pthread_join(meta->phth[i], NULL);
//		printf("n is %i\n", meta->times[i]);
	}
	pthread_join(monitor, NULL);
	ft_free_philo(&philo, &meta, n_phil);
	return (0);
}

void *ft_free_philo(t_phil **philo, t_glob **meta, int n_phil)
{
	int	i;

	i = 0;
	if (*meta)
	{
		if ((*meta)->fork)
			while (i < n_phil)
				pthread_mutex_destroy(&((*meta)->fork[i++]));
		pthread_mutex_destroy(&(*meta)->print);
		pthread_mutex_destroy(&(*meta)->test);
		ft_free((void *)&(*meta)->phth);
		ft_free((void *)&(*meta)->fork);
		ft_free((void *)&(*meta)->times);
	}
	ft_free((void *)meta);
	ft_free((void *)philo);
	return (NULL);
}
