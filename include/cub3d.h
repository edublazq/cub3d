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

typedef struct s_game
{
	struct s_map	map;
	mlx_t			mlx;
	int				fd;
}	t_game;

/* Singleton pattern */
t_game	*get_game(void);

int	check_arg(int ac, char **av);

#endif
