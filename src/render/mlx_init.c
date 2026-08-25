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

void	draw_square(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			px = x * TILE_SIZE + j;
			py = y * TILE_SIZE + i;
			if (px >= 0 && px < game->width
				&& py >= 0 && py < game->height)
				mlx_put_pixel(game->img, px, py, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (int)((game->player.pos).x * TILE_SIZE) - PLAYER_SIZE / 2;
	y = (int)((game->player.pos).y * TILE_SIZE) - PLAYER_SIZE / 2;

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_put_pixel(game->img, x + j, y + i, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void draw_map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while((game->map.grid)[y])
	{
		x = 0;
		while((game->map.grid)[y][x])
		{
			if ((game->map.grid)[y][x] == '1')
				draw_square(game, x, y, 0xFFFFFFFF);
			else if ((game->map.grid)[y][x] == '0')
				draw_square(game, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	draw_player(game);
}

int	can_move(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;

	return (game->map.grid[map_y][map_x] == '0');
}

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

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.orientation.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.orientation.y * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.orientation.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.orientation.y * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.orientation.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.orientation.x * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.orientation.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.orientation.x * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
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
