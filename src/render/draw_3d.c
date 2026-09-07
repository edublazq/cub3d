/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:10:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:10:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_column(t_game *game, void *img, int x, t_ray *ray)
{
	t_column		col;
	mlx_texture_t	*texture;
	double			step;
	int				y;

	init_column(&col, ray, game->height);
	col.texture = pick_wall_texture(ray);
	texture = game->map.textures[col.texture];
	col.tex_vec.x = calc_tex_x(*ray, texture);
	step = init_tex_pos(&col, texture, game->height);
	y = -1;
	while (++y < game->height)
	{
		if (y < col.draw_start)
			mlx_put_pixel(img, x, y, game->map.ceiling_color.rgba);
		else if (y > col.draw_end)
			mlx_put_pixel(img, x, y, game->map.floor_color.rgba);
		else
			mlx_put_pixel(img, x, y, sample_wall_color(&col, texture, step));
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
		draw_column(game, game->img, x, &ray);
		x++;
	}
}
