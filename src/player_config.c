/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 11:39:25 by edblazqu          #+#    #+#             */
/*   Updated: 2026/07/08 11:39:27 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	config_player(t_player *player)
{
	double	plane_mag;
	double	dir_angle;

	player->movement_speed = 1.0f;
	player->rotate_speed = 0.5f;
	player->pos = (t_vec2){2, 2};
	player->fov = 60;
	dir_angle = -PI / 2;
	plane_mag = tan((player->fov * PI / 180.0f) / 2.0);
	player->dir = (t_vec2){cos(dir_angle), sin(dir_angle)};
	player->plane = vec2_scale(vec2_perp(player->dir), plane_mag);
}
