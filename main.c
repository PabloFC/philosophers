/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafuente <pafuente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:28:55 by pafuente          #+#    #+#             */
/*   Updated: 2025/07/10 10:28:55 by pafuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (init_all(&rules, argc, argv))
		return (1);
	if (start_simulation(&rules))
	{
		cleanup(&rules);
		return (1);
	}
	cleanup(&rules);
	return (0);
}
