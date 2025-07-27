/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:49 by imellali          #+#    #+#             */
/*   Updated: 2025/07/27 12:25:40 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc < 5 || argc > 6)
		return (ft_man(), -1);
	if (ft_parse(argc, argv, &sim.config))
		return (ft_man(), -1);
	if (init_simulation(&sim))
		return (cleanup_simulation(&sim), -1);
	// TODO: Later you'll add thread creation here
	printf("init success\n");
	cleanup_simulation(&sim);
	return (0);
}
