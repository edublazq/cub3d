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

/* void	main_hooks(mlx_key_data_t keydata, void *param)
{
} */

void	init_window(mlx_t *mlx)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!mlx)
		return ;
	// mlx_loop_hook(mlx, &main_hooks, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
