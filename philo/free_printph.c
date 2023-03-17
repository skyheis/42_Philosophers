/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:51:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/17 09:45:52 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
		printf("%-7li %2i has taken a fork 🍴\n",
			get_time() - philo->start_time, philo->phid + 1);
	pthread_mutex_unlock(&(philo->meta->print));
}

void	print_eat(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
		printf("%-7li %2i is eating 🍝\n",
			get_time() - philo->start_time, philo->phid + 1);
	pthread_mutex_unlock(&(philo->meta->print));
}

void	print_sleeping(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
		printf("%-7li %2i is sleeping 💤\n",
			get_time() - philo->start_time, philo->phid + 1);
	pthread_mutex_unlock(&(philo->meta->print));
}

void	print_think(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
		printf("%-7li %2i is thinking 💭\n",
			get_time() - philo->start_time, philo->phid + 1);
	pthread_mutex_unlock(&(philo->meta->print));
}

int	ft_free_philo(t_phil **philo, t_glob **meta, int n_phil)
{
	int	i;

	if (*meta)
	{
		i = 0;
		if ((*meta)->fork)
			while (i < n_phil)
				pthread_mutex_destroy(&((*meta)->fork[i++]));
		pthread_mutex_destroy(&(*meta)->print);
		ft_free((void *)&(*meta)->phth);
		ft_free((void *)&(*meta)->fork);
		ft_free((void *)&(*meta)->times);
		ft_free((void *)&(*meta)->last_meal);
	}
	ft_free((void *)meta);
	ft_free((void *)philo);
	return (1);
}
