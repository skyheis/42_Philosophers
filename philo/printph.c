/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:51:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/02 16:21:53 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
		printf("%-7li %2i has taken a fork 🍴\n",
				philo->start_time, philo->phid + 1);
	pthread_mutex_unlock(&(philo->meta->print));
}

void	print_eat(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
		printf("%-7li %2i is eating 🍝\n",
				philo->start_time, philo->phid + 1);
	pthread_mutex_unlock(&(philo->meta->print));
}

void	print_sleeping(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
		printf("%-7li %2i is sleeping 💤\n",
				philo->start_time, philo->phid + 1);
	pthread_mutex_unlock(&(philo->meta->print));
}

void	print_die(t_phil *philo)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->dead)
	{
		printf("%-7li %2i dead 💀\n",
				philo->start_time, philo->phid + 1);
		philo->meta->dead = 1;
	}
	pthread_mutex_unlock(&(philo->meta->print));
}
