/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:51:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/15 16:10:52 by ggiannit         ###   ########.fr       */
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

void	print_die(t_glob *meta, int i)
{
	pthread_mutex_lock(&meta->print);
	if (!meta->dead)
	{
		printf("%-7li %2i is dead 💀\n",
				get_time() - meta->start_time, i + 1);
	}
	pthread_mutex_unlock(&meta->print);
}
