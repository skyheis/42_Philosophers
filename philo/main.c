/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:31:30 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/02 13:59:00 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_utoi(const char *num)
{
	int	k;
	int	toi;

	k = 0;
	toi = 0;
	while (num[k] == 32 || (num[k] >= 9 && num[k] <= 13))
		k++;
	while (num[k] >= '0' && num[k] <= '9')
	{
		toi *= 10;
		toi += num[k] - 48;
		k++;
	}
	return (toi);
}

int	ft_check_args(int ac, char **av)
{
	int	i;
	int	k;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (i < ac)
	{
		k = 0;
		while (av[i][k])
		{
			if (av[i][k] < '0' || av[i][k] > '9')
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

void *ft_free(void **point)
{
	if (*point)
	{
		free(*point);
		*point = NULL;
	}
	return (NULL);
}

/*void *ft_free_philo(t_phil **philo)
{
	int	i;

	i = 0;
	if ((*philo)->fork)
		while (i < (*philo)->n_phil)
			pthread_mutex_destroy(&((*philo)->fork[i++]));
	ft_free((void *) (*philo)->fork);
	ft_free((void *) (*philo)->fork);
	ft_free((void *) (*philo)->phth);
	ft_free((void *) philo);
	return (NULL);
}

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

void	printph(t_phil *philo, int action)
{
	int time = 42;

	pthread_mutex_lock(&philo->meta->print);
	if (philo->meta->dead)
	{
		pthread_mutex_unlock(&(philo->meta->print));
		return ;
	}
	if (action == FORK)
		printf("%-7i %2i has taken a fork 🍴\n", time, philo->phid + 1);
	else if (action == EAT)
		printf("%-7i %2i is eating 🍝\n", time, philo->phid + 1);
	else if (action == SLEEP)
		printf("%-7i %2i is sleeping 💤\n", time, philo->phid + 1);
	else if (action == THINK)
		printf("%-7i %2i is thinking 💭\n", time, philo->phid + 1);
	else if (action == DIE)
	{
		printf("%-7i %2i dead 💀\n", time, philo->phid + 1);
		philo->meta->dead = 1;
	}
	pthread_mutex_unlock(&(philo->meta->print));
}

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

void	*rout_test(t_phil *philo)
{
	int i = 0;

	while (i++ < 1000)
	{
		//pthread_mutex_lock(&philo->meta->test);
		philo->meta->times[philo->phid] += 1;
		//pthread_mutex_unlock(&philo->meta->test);
	}
	printph(philo, FORK);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_phil	*philo;
	t_glob	*meta;
	int		n_phil;
	int		i = 0;

	if (ac != 3)
		return (42);
	n_phil = ft_utoi(av[1]);
	philo = (t_phil *) malloc(n_phil * sizeof(t_phil));
	if (!philo)
		return (1);
	meta = (t_glob *) malloc(sizeof(t_glob));
	if (!meta)
		return (2);
	while (i < n_phil)
	{
		philo[i].phid = i;
		philo[i].meta = meta;
		i++;
	}
	meta->times = (int *) malloc(n_phil * sizeof(int));
	if (!meta->times)
		return (3);
	i = -1;
	while (++i < n_phil)
		meta->times[i] = ft_utoi(av[2]);//5
	meta->fork = NULL;
	pthread_mutex_init(&meta->print, NULL);
	
	meta->dead = 0;
	pthread_mutex_init(&meta->test, NULL);
	/*meta->fork = (pthread_mutex_t *) malloc(n_phil * sizeof(pthread_mutex_t));
	if (!meta->fork)
		return (4);
	i = -1;
	while (++i < n_phil)
		pthread_mutex_init(&meta->fork[i++], NULL);*/
	i = -1;
	meta->phth = (pthread_t *) malloc(n_phil * sizeof(pthread_t));
	while (++i < n_phil)
	{
		pthread_create(&meta->phth[i], NULL, (void *) rout_test, &philo[i]);
	}
	i = -1;
	while (++i < n_phil)
	{
		pthread_join(meta->phth[i], NULL);
//		printf("n is %i\n", meta->times[i]);
	}
	pthread_mutex_destroy(&meta->print);
	pthread_mutex_destroy(&meta->test);
	ft_free((void *)&meta->phth);
	ft_free((void *)&meta->times);
	ft_free((void *)&philo);
	ft_free((void *)&meta);
	return (0);
}
