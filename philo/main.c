/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:31:30 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/27 18:06:04 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_utoi(const char *num)
{
	int	k;
	int	sgn;
	int	toi;

	k = 0;
	toi = 0;
	sgn = 1;
	while (num[k] == 32 || (num[k] >= 9 && num[k] <= 13))
		k++;
	while (num[k] >= '0' && num[k] <= '9')
	{
		toi *= 10;
		toi += num[k] - 48;
		k++;
	}
	return (toi * sgn);
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

t_phil	*ft_init_philo(int ac, char **av)
{
	t_phil	*philo;

	if (ft_check_args(ac, av))
	philo = (t_phil *) malloc(sizeof(t_phil));
	if (!philo)
		return (philo);
	philo->n_phil = ft_utoi(av[1]);
}

int	main(int ac, char **av)
{
	t_phil	*philo;

	philo = ft_init_philo(ac, av);

}
