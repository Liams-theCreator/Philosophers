/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:49 by imellali          #+#    #+#             */
/*   Updated: 2025/04/30 16:35:55 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_data		data;

	if (ft_parse(argc, argv, &config))
	{
		ft_usage(argv[0]);
		return (1);
	}
	if (init_data(&data, &config))
	{
		write(2, "Error: initialization failed\n", 28);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
