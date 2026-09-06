/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:10:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:10:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	pick_wall_color(t_ray *ray)
{
	if (ray->side == 1)
		return (0x888888FF);
	return (0xCCCCCCFF);
}

/* static int	pick_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			game->
	}
} */

void	draw_column(void *img, int x, t_ray *ray, int screen_height)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	uint32_t	color;
	int			y;

	line_height = (int)(screen_height / ray->perp_wall_dist);
	draw_start = -line_height / 2 + screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + screen_height / 2;
	if (draw_end >= screen_height)
		draw_end = screen_height - 1;
	color = pick_wall_color(ray);
	y = -1;
	while (++y < screen_height)
	{
		if (y < draw_start)
			mlx_put_pixel(img, x, y, 0x800000FF);
		else if (y > draw_end)
			mlx_put_pixel(img, x, y, 0x808000FF);
		else
			mlx_put_pixel(img, x, y, color);
	}
}

void	draw_3d(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->width)
	{
		ray = compute_ray(&game->player, &game->map, x, game->width);
		draw_column(game->img, x, &ray, game->height);
		x++;
	}
}
