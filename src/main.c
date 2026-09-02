/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:33:44 by edblazqu          #+#    #+#             */
/*   Updated: 2026/05/30 15:33:45 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_game game;

 	if (check_arg(ac, av))
		return (EXIT_FAILURE);
	get_data_for_map(&(game.map), av[1]);
	get_data_for_player(&(game.player), &(game.map));
	init_window(&game);
	return (free(game.map.textures), free_argv((&(game.map))->grid), 0);
}
