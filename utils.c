/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:19:37 by imellali          #+#    #+#             */
/*   Updated: 2025/04/30 16:20:02 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			ms;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}
