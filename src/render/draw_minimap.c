/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:10:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:10:01 by edblazqu         ###   ########.fr       */
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

void	draw_line(t_game *game, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = 1;
	sy = 1;
	if (x0 > x1)
		sx = -1;
	if (y0 > y1)
		sy = -1;
	err = dx - dy;
	while (1)
	{
		if (x0 >= 0 && x0 < game->width
			&& y0 >= 0 && y0 < game->height)
			mlx_put_pixel(game->img, x0, y0, 0xFF0000FF);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_direction(t_game *game)
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;

	start_x = (int)(game->player.pos.x * TILE_SIZE);
	start_y = (int)(game->player.pos.y * TILE_SIZE);

	end_x = start_x + (int)(game->player.orientation.x * TILE_SIZE);
	end_y = start_y + (int)(game->player.orientation.y * TILE_SIZE);

	draw_line(game, start_x, start_y, end_x, end_y);
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (int)(game->player.pos.x * TILE_SIZE) - PLAYER_SIZE / 2;
	y = (int)(game->player.pos.y * TILE_SIZE) - PLAYER_SIZE / 2;

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
	draw_direction(game);
}

void draw_map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				draw_square(game, x, y, 0xFFFFFFFF);
			else if (game->map.grid[y][x] == '0')
				draw_square(game, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	draw_player(game);
}
