/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 12:48:37 by edblazqu          #+#    #+#             */
/*   Updated: 2026/08/31 12:48:41 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	init_ray_grid(t_ray *ray, t_player *player)
{
	ray->map_x = (int)player->pos.x;
	ray->map_y = (int)player->pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

static void	init_ray_steps(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (player->pos.x - ray->map_x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (player->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
	}
}

t_vec2	get_ray_dir(t_player *player, int x, int screen_width)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)screen_width - 1.0;
	return (vec2_add(player->orientation,
			vec2_scale(player->plane, camera_x)));
}

static void	perform_dda(t_ray *ray, t_map *map)
{
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(map, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

t_ray	compute_ray(t_player *player, t_map *map, int x, int screen_width)
{
	t_ray	ray;

	ray.dir = get_ray_dir(player, x, screen_width);
	ray.hit = 0;
	init_ray_grid(&ray, player);
	init_ray_steps(&ray, player);
	perform_dda(&ray, map);
	ray.perp_wall_dist = calc_perp_wall_dist(ray, player);
	return (ray);
}
