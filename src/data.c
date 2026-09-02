/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:35:33 by edblazqu          #+#    #+#             */
/*   Updated: 2026/05/30 15:35:34 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    get_data_for_player(t_player *player, t_map *map)
{
    int i;
    int j;
    char c;

    i = 0;
    while ((map->grid)[i])
    {
        j = 0;
        while ((map->grid)[i][j])
        {
            c = map->grid[i][j];
            if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
            {
                if (c == 'N')
                {
                    (player->orientation).x = 0;
                    (player->orientation).y = -1;
                }
                else if (c == 'S')
                {
                    (player->orientation).x = 0;
                    (player->orientation).y = 1;
                }
                else if (c == 'E')
                {
                    (player->orientation).x = -1;
                    (player->orientation).y = 0;
                }
                else if (c == 'W')
                {
                    (player->orientation).x = 1;
                    (player->orientation).y = 0;
                }
                (player->pos).x = j + 0.5;
                (player->pos).y = i + 0.5;
                map->grid[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    player->fov = 60;
    player->plane = vec2_scale(vec2_perp(player->orientation),
            tan((player->fov * PI / 180.0) / 2.0));
}
