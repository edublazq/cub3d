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

t_game	*game(void)
{
	static t_game	game_struct;
	return (&game_struct);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
/* 	if (check_arg(ac, av))
		return (EXIT_FAILURE); */
	init_window(&(game()->mlx));
	return (0);
}
