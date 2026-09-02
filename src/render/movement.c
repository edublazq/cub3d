/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopelayo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 19:16:51 by jopelayo          #+#    #+#             */
/*   Updated: 2026/08/26 19:16:53 by jopelayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;

	return (game->map.grid[map_y][map_x] == '0');
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.orientation.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.orientation.y * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.orientation.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.orientation.y * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.orientation.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.orientation.x * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.orientation.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.orientation.x * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
}

void	rotate_right(t_game *game)
{
	game->player.orientation = vec2_rotate(game->player.orientation, ROT_SPEED);
	game->player.plane = vec2_rotate(game->player.plane, ROT_SPEED);
}

void	rotate_left(t_game *game)
{
	game->player.orientation = vec2_rotate(game->player.orientation, -ROT_SPEED);
	game->player.plane = vec2_rotate(game->player.plane, -ROT_SPEED);
}