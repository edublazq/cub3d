/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:35:33 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/07 23:43:07 by jopelayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_textures(char *line)
{
	int	len;
	int error;

	error = 0;
	len = ft_strlen(line);
	if (ft_strncmp(line, "NO ", 3) && ft_strncmp(line, "SO ", 3)
		&& ft_strncmp(line, "WE ", 3) && ft_strncmp(line, "EA ", 3))
	{
		error++;
	}
	if (ft_strncmp(&line[len - 5], ".png", 4))
	{
		error++;
	}
	return (error);
}

int	check_file(char **content, int error, int i)
{
	int	max;

	max = 0;
	while (content[i][0] != '1' && max < 5)
	{
		if (content[i][0] == '\n')
		{
			i++;
			continue;
		}
		if (check_textures(content[i]) && check_colors(content[i], 0))
			error++;
		max++;
		i++;
	}
	if (error != 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
