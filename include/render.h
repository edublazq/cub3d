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

# include "cub3d.h"
# include "types.h"

typedef struct s_game	t_game;
typedef struct s_ray	t_ray;
typedef struct s_player	t_player;
typedef struct s_map	t_map;
typedef struct s_colors	t_colors;
typedef struct s_texture	t_texture;

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
t_ray	compute_ray(t_player *player, t_map *map, int x, int screen_width);
void	draw_3d(t_game *game);

#endif
