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

#include "cub3d.h"

static mlx_image_t	*g_img;

static void	draw_noise(void)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < g_img->width)
	{
		y = 0;
		while (y < g_img->height)
		{
			mlx_put_pixel(g_img, x, y, ((uint32_t)(rand() & 0xFFFFFF) << 8) | 0xFF);
			y++;
		}
		x++;
	}
}

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	(void)param;
	mlx_resize_image(g_img, width, height);
	draw_noise();
}

void	main_hooks(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
	{
		printf("%d %d\n", mlx->width, mlx->height);
		draw_noise();
	}
}

void	init_window(mlx_t *mlx)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
		return ;
	g_img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!g_img)
		return (mlx_terminate(mlx));
	draw_noise();
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &main_hooks, mlx);
	mlx_resize_hook(mlx, &resize_hook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
