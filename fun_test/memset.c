/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:56:01 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/01 12:03:02 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

int main()
{
	int *lol = malloc(10 * sizeof(int));
	int i = 0;

	memset(lol, (unsigned char) 42, 10 * sizeof(int));
	while (i < 10)
	{
		printf("%i %i\n", i, lol[i]);
		i++;
	}
}
