/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:18:53 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/02 11:28:26 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void ft_foo(int i)
{
	sleep(i);
}

time_t	get_time_a(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000));
}

time_t	get_time_b(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int main()
{
	struct timeval pre;
	struct timeval pos;

	gettimeofday(&pre, NULL); 
	printf("pre %lu %lu\n", pre.tv_sec, pre.tv_usec);
	ft_foo(1);
	gettimeofday(&pos, NULL); 
	printf("pos %lu %lu\n", pos.tv_sec, pos.tv_usec);
	sleep(1);
	printf("time a %lu\n", get_time_a());
	printf("time b %lu\n", get_time_b());
}
