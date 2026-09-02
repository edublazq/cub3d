/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:27:49 by edblazqu          #+#    #+#             */
/*   Updated: 2026/07/08 12:27:50 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			px = x * TILE_SIZE + j;
			py = y * TILE_SIZE + i;
			if (px >= 0 && px < game->width
				&& py >= 0 && py < game->height)
				mlx_put_pixel(game->img, px, py, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (int)((game->player.pos).x * TILE_SIZE) - PLAYER_SIZE / 2;
	y = (int)((game->player.pos).y * TILE_SIZE) - PLAYER_SIZE / 2;

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_put_pixel(game->img, x + j, y + i, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void draw_map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while(game->map.grid[y])
	{
		x = 0;
		while((game->map.grid)[y][x])
		{
			if ((game->map.grid)[y][x] == '1')
				draw_square(game, x, y, 0xFFFFFFFF);
			else if ((game->map.grid)[y][x] == '0')
				draw_square(game, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	draw_player(game);
}

static uint32_t	pick_wall_color(t_ray *ray)
{
	if (ray->side == 1)
		return (0x888888FF);
	return (0xCCCCCCFF);
}

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
