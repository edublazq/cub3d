/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 12:48:29 by edblazqu          #+#    #+#             */
/*   Updated: 2026/07/06 12:48:34 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	start_window(t_mlx *mlx)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx->main = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!mlx->main)
		return ; 
}

void	main_hooks(t_mlx *mlx)
{

}
