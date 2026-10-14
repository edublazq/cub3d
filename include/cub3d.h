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

# define TEXTURES_AND_COLORS 1
# define MAP				 2

typedef struct s_colors
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	rgba;
}	t_colors;

typedef struct s_map
{
	mlx_texture_t	*textures[4];
	t_colors		floor_color;
	t_colors		ceiling_color;
	char			**grid;
	int				height;
	int				width;
}	t_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	orientation;
	t_vec2	plane;
	int		fov;
}	t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	double	wall_x;
	t_vec2	dir;
	t_vec2	delta_dist;
	t_vec2	side_dist;
}	t_ray;

typedef struct s_game
{
	struct s_player	player;
	struct s_map	map;
	int				width;
	int				height;
	mlx_t			*mlx;
	void			*img;
	int				moved;
}	t_game;

/* Validación y parseo */

char	**read_file(char *file, char *line, int fd, int i);
int		check_arg(int ac, char **av);
int		check_file(char **content, int error, int i);
int		check_map(char **content, size_t longest, int i, int j);
int		check_colors(char *line, int i);
int		check_textures(char *line);
char	*line_with_only_numbers(char *line, char *new_line);
int		get_map_start(char **content);
int		tally_headers(char **content, int header_end, int start);
int		build_and_validate_map(char **content, int end, int j,
			size_t longest);
void	free_matrix(char **argv);
void	free_textures(mlx_texture_t *textures[4]);
int		get_data_for_map(t_map *map, char *file);
char	**get_map(char **aux);
double	get_speed(t_game *game);
int		parse_header_line(t_map *map, char *line);
void	get_colors(char *line, t_colors *out);
void	get_data_for_player(t_player *player, t_map *map);
int		is_void(char c);
int		is_walkable(char c);

#endif
