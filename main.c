/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:49 by imellali          #+#    #+#             */
/*   Updated: 2025/07/25 08:18:21 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if (ft_parse(argc, argv, &config))
	{
		ft_usage(argv[0]);
		return (-1);
	}
	return (0);
}
