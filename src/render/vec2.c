/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 12:56:36 by edblazqu          #+#    #+#             */
/*   Updated: 2026/07/06 12:56:39 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	t_vec2	new_vec;

	new_vec.x = a.x + b.x;
	new_vec.y = a.y + b.y;
	return (new_vec);
}

t_vec2	vec2_scale(t_vec2 vec, double scale)
{
	t_vec2	new_vec;

	new_vec.x = vec.x * scale;
	new_vec.y = vec.y * scale;
	return (new_vec);
}

t_vec2	vec2_rotate(t_vec2 vec, double rad)
{
	t_vec2	new_vec;

	new_vec.x = vec.x * cos(rad) - vec.y * sin(rad);
	new_vec.y = vec.x * sin(rad) + vec.y * cos(rad);
	return (new_vec);
}

t_vec2	vec2_perp(t_vec2 vec)
{
	return ((t_vec2){-vec.y, vec.x});
}
