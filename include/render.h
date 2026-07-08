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
# define WIDTH 800
# define HEIGHT 800
# define KEY_ESC 65307
# define ON_DESTROY 17

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

/* GESTION DE VECTORES */

t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_scale(t_vec2 vec, double scale);
t_vec2	vec2_rotate(t_vec2 vec, double rad);

#endif
