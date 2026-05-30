/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:35:33 by edblazqu          #+#    #+#             */
/*   Updated: 2026/05/30 15:35:34 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_arg(int ac, const char **av)
{
	int	len;

	if (ac != 2)
		return (EXIT_FAILURE);
	len = ft_strlen(av[1]);
	if (len <= 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
