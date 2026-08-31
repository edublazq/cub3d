/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:31:59 by edblazqu          #+#    #+#             */
/*   Updated: 2026/08/31 14:32:00 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	is_wall(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (EXIT_FAILURE);
	return (map->grid[y][x] != '0');
}
