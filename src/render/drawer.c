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
	while((game->map.grid)[y])
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
