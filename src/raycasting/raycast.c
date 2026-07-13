/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:53:33 by edblazqu          #+#    #+#             */
/*   Updated: 2026/07/13 14:53:34 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_grid(t_ray *ray, t_player *player)
{
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.y);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

static void	init_ray_steps(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
        ray->step.x = 1;
        ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->pos.y) * ray->delta_dist_y;
    }
}

t_ray	computer_ray(t_player *player, t_map *map, int x, int screen_width)
{

}
