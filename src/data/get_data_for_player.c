/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_for_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 00:00:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/06 00:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

static void	set_orientation(t_player *player, char c)
{
	if (c == 'N')
	{
		player->orientation.x = 0;
		player->orientation.y = -1;
	}
	else if (c == 'S')
	{
		player->orientation.x = 0;
		player->orientation.y = 1;
	}
	else if (c == 'E')
	{
		player->orientation.x = -1;
		player->orientation.y = 0;
	}
	else if (c == 'W')
	{
		player->orientation.x = 1;
		player->orientation.y = 0;
	}
}

static void	find_spawn_point(t_map *map, t_player *player)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			c = map->grid[i][j];
			if (is_spawn_char(c))
			{
				set_orientation(player, c);
				player->pos.x = j + 0.5;
				player->pos.y = i + 0.5;
				map->grid[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

static void	set_camera_plane(t_player *player)
{
	player->fov = 60;
	player->plane = vec2_scale(vec2_perp(player->orientation),
			tan((player->fov * PI / 180.0) / 2.0));
}

void	get_data_for_player(t_player *player, t_map *map)
{
	find_spawn_point(map, player);
	set_camera_plane(player);
}
