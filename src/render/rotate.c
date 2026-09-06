/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopelayo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:15:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:15:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_game *game)
{
	game->player.orientation = vec2_rotate(game->player.orientation, ROT_SPEED);
	game->player.plane = vec2_rotate(game->player.plane, ROT_SPEED);
}

void	rotate_left(t_game *game)
{
	game->player.orientation = vec2_rotate(game->player.orientation,
			-ROT_SPEED);
	game->player.plane = vec2_rotate(game->player.plane, -ROT_SPEED);
}
