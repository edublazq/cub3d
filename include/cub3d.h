/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:30:36 by edblazqu          #+#    #+#             */
/*   Updated: 2026/05/30 15:30:37 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# define PI 3.141592f
# define WIDTH 1920
# define HEIGHT 1080
# define KEY_ESC 65307
# define ON_DESTROY 17


typedef struct s_texture
{
	char	*no;
	char	*ea;
	char	*so;
	char	*we;
}	t_texture;

typedef struct s_map
{
	struct s_texture	textures;
	char				**grid;
	int					rows;
	int					cols;
}	t_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
	double	movement_speed;
	double	rotate_speed;
	int		fov;
}	t_player;

typedef struct s_game
{
	struct s_player	player;
	struct s_map	map;
	mlx_t			mlx;
	int				fd;
}	t_game;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_ray
{
	t_vec2	map;
	t_vec2	dir;
	t_vec2	delta_dist;
	t_vec2	step;
	t_vec2	side_dist;
	double	perp_wall_distance;
	int		hit;
	int		side;
}	t_ray;

/* GESTION DE VECTORES */

t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_scale(t_vec2 vec, double scale);
t_vec2	vec2_rotate(t_vec2 vec, double rad);
t_vec2	vec2_perp(t_vec2 vec);

/* MLX */
void	init_window(mlx_t *mlx);

/* RAYCASTING */

t_ray	computer_ray(t_player *player, t_map *map, int x, int screen_width);


/* Singleton pattern */

t_game	*game(void);

/* Parseo */

int	check_arg(int ac, char **av);

/* Configuracion */

void	config_player(t_player *player);

#endif
