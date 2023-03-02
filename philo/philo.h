/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:02:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/02 11:06:53 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_phil
{
	unsigned int	phid;
	struct s_glob	*meta;
}					t_phil;

typedef struct s_glob
{
	int				clock;
	int				*times;
	pthread_t		*phth;
	pthread_mutex_t	*fork;
	int				dead;
	pthread_mutex_t	print;
	pthread_mutex_t	test;
}					t_glob;

/*typedef struct s_glob
{
	int				n_phil;
	pthread_t		*phth;
	pthread_mutex_t	*fork;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	//unsigned int	time_think;
	int				n_times;
	int				*times;
}					t_glob;*/




#endif

/* gettimeofday
 * struct timeval {
 * time_t tv_sec; lu
 * suseconds_t tv_usec; lu
 * }
 * args: &timeval, NULL
*/
