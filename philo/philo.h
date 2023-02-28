/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:02:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/27 18:16:47 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_phil
{
	char			n_phil;
	char			*fork;
	unsigned int	time_sleep;
	unsigned int	time_eat;
	unsigned int	time_think;
	unsigned int	time_die;
	int				times;
}					t_phil;


#endif

/* gettimeofday
 * struct timeval {
 * time_t tv_sec; lu
 * suseconds_t tv_usec; lu
 * }
 * args: &timeval, NULL
*/
