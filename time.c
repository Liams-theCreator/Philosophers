/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:40:52 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 13:44:19 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long	start;
	//long	current;

	if (ms <= 0)
		return ;
	start = current_time();
	while (current_time() - start < ms)
	{
		//current = current_time();
		//if (current - start >= ms)
		//	break ;
		usleep(100);
	}
}
