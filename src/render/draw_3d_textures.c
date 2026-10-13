/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 12:00:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/07 12:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex_side	pick_wall_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (EAST_TEXTURE);
		return (WEST_TEXTURE);
	}
	if (ray->step_y > 0)
		return (NORTH_TEXTURE);
	return (SOUTH_TEXTURE);
}

double	calc_tex_x(t_ray ray, mlx_texture_t *texture)
{
	double	tex_x;

	tex_x = (int)(ray.wall_x * texture->width);
	if (ray.side == 0 && ray.dir.x < 0)
		tex_x = texture->width - tex_x - 1;
	if (ray.side == 1 && ray.dir.y > 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	init_column(t_column *col, t_ray *ray, t_game *game)
{
	double	scale;

	scale = game->width / (2.0 * hypot(game->player.plane.x,
				game->player.plane.y));
	col->line_height = (int)(scale / ray->perp_wall_dist);
	col->draw_start = -col->line_height / 2 + game->height / 2;
	if (col->draw_start < 0)
		col->draw_start = 0;
	col->draw_end = col->line_height / 2 + game->height / 2;
	if (col->draw_end >= game->height)
		col->draw_end = game->height - 1;
}

double	init_tex_pos(t_column *col, mlx_texture_t *tex, int screen_h)
{
	double	step;

	step = (double)tex->height / col->line_height;
	col->tex_vec.y = (col->draw_start - screen_h / 2
			+ col->line_height / 2) * step;
	return (step);
}

uint32_t	sample_wall_color(t_column *col, mlx_texture_t *tex, double step)
{
	int		idx;
	uint8_t	*p;
	int		tex_y;

	tex_y = (int)col->tex_vec.y % (int)tex->height;
	idx = ((int)tex_y * tex->width + (int)col->tex_vec.x)
		* tex->bytes_per_pixel;
	p = &tex->pixels[idx];
	col->tex_vec.y += step;
	return (((uint32_t)p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}
