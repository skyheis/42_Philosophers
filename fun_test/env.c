/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:16:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/28 10:19:24 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

int main(int ac, char **av, char **env)
{
	int i = 0;
	int k = 0;

	while (env[i])
	{
		k = 0;
		while (env[i][k])
		{
			write(1, &env[i][k], 1);
			k++;
		}
		write(1, "\n", 1);
		i++;
	}
}

