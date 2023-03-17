/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:02:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/17 09:43:32 by ggiannit         ###   ########.fr       */
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

# define PHIL 1
# define DIE 2
# define EAT 3
# define SLEEP 4
# define TIMES 5

typedef struct s_phil
{
	time_t			start_time;
	unsigned int	phid;
	unsigned int	next_fork;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	struct s_glob	*meta;
}					t_phil;

typedef struct s_glob
{
	int				clock;//serve?
	int				n_phil;
	int				*times;
	time_t			*last_meal;
	time_t			start_time;
	unsigned int	time_die;
	pthread_t		*phth;
	pthread_mutex_t	*fork;
	int				dead;
	pthread_mutex_t	print;
}					t_glob;

void	monitor_death(t_glob *meta);
void	philo_life(t_phil *philo);

/* init all */
void	ft_start_dinner(t_glob *meta, t_phil *philo, int n_phil);
int		ft_init_mutex(t_glob *meta, int n_phil);
int		ft_init_meta_philo(t_glob *meta, t_phil *philo, int ac, char **av);


int		ft_free_philo(t_phil **philo, t_glob **meta, int n_phil);
void	ft_msleep(unsigned int x);

/* printph  */
void	print_fork(t_phil *philo);
void	print_eat(t_phil *philo);
void	print_sleeping(t_phil *philo);
void	print_think(t_phil *philo);
void	print_die(t_glob *meta, int i);

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
