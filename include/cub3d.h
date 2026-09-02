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
# include "render.h"
# include "gnl.h"
# include "types.h"

typedef struct s_texture
{
	char	*no;
	char	*ea;
	char	*so;
	char	*we;
}	t_texture;

typedef struct s_colors
{
	int		one;
	int		two;
	int		three;
}	t_colors;

typedef struct s_map
{
	t_texture	*textures;
    t_colors	floor_color;
    t_colors	ceiling_color;
	char		**grid;
	int			height;
	int			width;
}	t_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	orientation;
	double	movement_speed;
	t_vec2	plane;
	double	rotate_speed;
	int		fov;
}	t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	t_vec2	dir;
	t_vec2	delta_dist;
	t_vec2	side_dist;
	int		side;
	int		hit;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_game
{
	struct s_player	player;
	struct s_map	map;
	int				width;
	int				height;
	mlx_t			*mlx;
	int				fd;
	void			*img;
}	t_game;

/* Validación y parseo */

char 	**read_file(char *file);
int		check_arg(int ac, char **av);
int 	check_file(char **content);
int 	check_map(char **file_content);
void	free_argv(char **argv);
int		get_data_for_map(t_map *map, char *file);
char	**get_map(char **aux);
int		parse_header_line(t_map *map, char **content, int i);
void	get_data_for_player(t_player *player, t_map *map);
int		is_void(char c);
int		is_walkable(char c);

/* Configuracion */

void	config_player(t_player *player);

#endif
