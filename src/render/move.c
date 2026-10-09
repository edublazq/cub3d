/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopelayo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:15:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:15:01 by edblazqu         ###   ########.fr       */
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
	double	speed;

	speed = get_speed(game);
	new_x = game->player.pos.x + game->player.orientation.x * speed;
	new_y = game->player.pos.y + game->player.orientation.y * speed;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
		game->moved = 1;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = get_speed(game);
	new_x = game->player.pos.x - game->player.orientation.x * speed;
	new_y = game->player.pos.y - game->player.orientation.y * speed;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
		game->moved = 1;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = get_speed(game);
	new_x = game->player.pos.x + game->player.orientation.y * speed;
	new_y = game->player.pos.y - game->player.orientation.x * speed;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
		game->moved = 1;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = get_speed(game);
	new_x = game->player.pos.x - game->player.orientation.y * speed;
	new_y = game->player.pos.y + game->player.orientation.x * speed;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
		game->moved = 1;
	}
}
