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

double	calc_perp_wall_dist(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		return ((ray->map_x - player->pos.x
				+ (1 - ray->step_x) / 2.0) / ray->dir.x);
	else
		return ((ray->map_y - player->pos.y
				+ (1 - ray->step_y) / 2.0) / ray->dir.y);
}
