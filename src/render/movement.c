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

int	can_move(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x - PLAYER_RADIUS);
	map_y = (int)(y - PLAYER_RADIUS);
	if (game->map.grid[map_y][map_x] != '0')
		return (0);

	map_x = (int)(x + PLAYER_RADIUS);
	map_y = (int)(y - PLAYER_RADIUS);
	if (game->map.grid[map_y][map_x] != '0')
		return (0);

	map_x = (int)(x - PLAYER_RADIUS);
	map_y = (int)(y + PLAYER_RADIUS);
	if (game->map.grid[map_y][map_x] != '0')
		return (0);

	map_x = (int)(x + PLAYER_RADIUS);
	map_y = (int)(y + PLAYER_RADIUS);
	if (game->map.grid[map_y][map_x] != '0')
		return (0);

	return (1);
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

void	move_right(t_game *game)
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

void	move_left(t_game *game)
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
	double	old_dir_x;

	old_dir_x = game->player.orientation.x;
	game->player.orientation.x = game->player.orientation.x * cos(ROT_SPEED) - game->player.orientation.y * sin(ROT_SPEED);
	game->player.orientation.y = old_dir_x * sin(ROT_SPEED) + game->player.orientation.y * cos(ROT_SPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;

	old_dir_x = game->player.orientation.x;
	game->player.orientation.x = game->player.orientation.x * cos(-ROT_SPEED) - game->player.orientation.y * sin(-ROT_SPEED);
	game->player.orientation.y = old_dir_x * sin(-ROT_SPEED) + game->player.orientation.y * cos(-ROT_SPEED);
}