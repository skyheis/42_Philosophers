/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:31:30 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/01 12:11:52 by ggiannit         ###   ########.fr       */
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

void *ft_free_philo(t_phil **philo)
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
}

int	main(int ac, char **av)
{
	t_phil	*philo;

	philo = ft_init_philo(ac, av);
	if (!philo)
		return (1);
	printf("n_phil %i\n", (int) philo->n_phil);
	printf("die    %u\n", philo->time_die);
	printf("eat    %u\n", philo->time_eat);
	printf("sleep  %u\n", philo->time_sleep);
	printf("times  %i\n", philo->times);
}
