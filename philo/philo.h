/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:02:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/04 20:58:24 by ggiannit         ###   ########.fr       */
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


/* devo lavorare sul tempo, ad ora do un init time a tutti
 * poi devo lavorare sulla logica, i dispari devono partire 
 * a distanza di 1ms di differenza.
 * devo travare il modo di dire fare il check sul tempo */

/* creare un monitor per vedere se uno muore? */

typedef struct s_phil
{
	time_t			start_time;
	unsigned int	phid;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	struct s_glob	*meta;
}					t_phil;

typedef struct s_glob
{
	int				clock;
	int				n_phil;
	int				*times;
	time_t			*last_meal;
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

void *ft_free_philo(t_phil **philo, t_glob **meta, int n_phil);

/* printph  */
void	print_fork(t_phil *philo);
void	print_eat(t_phil *philo);
void	print_sleeping(t_phil *philo);
void	print_die(t_phil *philo);

/* utils_n_checks */
int		ft_utoi(const char *num);
int		ft_check_args(int ac, char **av);
void	*ft_free(void **point);
time_t	get_time(void);

#endif

/* gettimeofday
 * struct timeval {
 * time_t tv_sec; lu
 * suseconds_t tv_usec; lu
 * }
 * args: &timeval, NULL
*/
