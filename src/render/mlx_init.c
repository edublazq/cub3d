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

// static mlx_image_t	*g_img;

// static void	draw_noise(t_game *game)
// {
// 	uint32_t	x;
// 	uint32_t	y;

// 	x = 0;
// 	while (x < g_img->width)
// 	{
// 		y = 0;
// 		while (y < g_img->height)
// 		{
// 			mlx_put_pixel(g_img, x, y, ((uint32_t)(rand() & 0xFFFFFF) << 8) | 0xFF);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->width = width;
	game->height = height;
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, width, height);
	if (!game->img)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	draw_map(game);
}

void	 main_hooks(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	draw_map(game);
}

void	init_window(t_game *game)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	game->width = WIDTH;
	game->height = HEIGHT;
	game->mlx = mlx_init(game->width, game->height, "cub3d", true);
	if (!game->mlx)
		return ;
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->img)
		return (mlx_terminate(game->mlx));
	draw_map(game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (mlx_terminate(game->mlx));
	mlx_loop_hook(game->mlx, &main_hooks, game);
	mlx_resize_hook(game->mlx, &resize_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
