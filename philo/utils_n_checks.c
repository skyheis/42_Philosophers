/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_n_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:12:38 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/01 12:13:48 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
