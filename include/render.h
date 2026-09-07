/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 12:55:07 by edblazqu          #+#    #+#             */
/*   Updated: 2026/07/06 12:55:10 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <math.h>
# define PI 3.141592f
# define WIDTH 1920
# define HEIGHT 1080
# define KEY_ESC 65307
# define ON_DESTROY 17
# define TILE_SIZE 25
# define PLAYER_SIZE 10
# define MOVE_SPEED 0.09
# define ROT_SPEED 0.02
# define PLAYER_RADIUS 0.15

# include "cub3d.h"
# include "types.h"

typedef struct s_game	t_game;
typedef struct s_ray	t_ray;
typedef struct s_player	t_player;
typedef struct s_map	t_map;
typedef struct s_colors	t_colors;
typedef struct s_texture	t_texture;

typedef enum e_tex_side
{
	NORTH_TEXTURE,
	EAST_TEXTURE,
	WEST_TEXTURE,
	SOUTH_TEXTURE
}	t_tex_side;

typedef struct s_column
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_vec2		tex_vec;
	t_tex_side	texture;
	uint32_t	color;
}	t_column;


/* GESTION DE VECTORES */

t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_scale(t_vec2 vec, double scale);
t_vec2	vec2_rotate(t_vec2 vec, double rad);
t_vec2	vec2_perp(t_vec2 vec);

/* MLX */
void	init_window(t_game *game);

/* MOVEMENT */

void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);

/* DRAWERS */

void	draw_map(t_game *game);
void	draw_player(t_game *game);
void	draw_square(t_game *game, int x, int y, uint32_t color);

/* RAY */

int		is_wall(t_map *map, int x, int y);
double	calc_wall_x(t_player *player, t_ray ray);
double	calc_perp_wall_dist(t_ray ray, t_player *player);
t_ray	compute_ray(t_player *player, t_map *map, int x, int screen_width);
void	draw_3d(t_game *game);

/* TEXTURAS */

t_tex_side	pick_wall_texture(t_ray *ray);
double		calc_tex_x(t_ray ray, mlx_texture_t *texture);
void		init_column(t_column *col, t_ray *ray, int screen_h);
double		init_tex_pos(t_column *col, mlx_texture_t *tex, int screen_h);
uint32_t	sample_wall_color(t_column *col, mlx_texture_t *tex, double step);

#endif
