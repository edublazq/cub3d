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

static int	check_textures(char *line, int error1, int error2, int i)
{
	int	len;

	len = ft_strlen(line);
	if (i == 0)
	{
		error1 = ft_strncmp(line, "NO ./", 4);
		error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
	}
	else if (i == 1)
	{
		error1 = ft_strncmp(line, "SO ./", 4);
		error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
	}
	else if (i == 2)
	{
		error1 = ft_strncmp(line, "WE ./", 4);
		error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
	}
	else if (i == 3)
	{
		error1 = ft_strncmp(line, "EA ./", 4);
		error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
	}
	return (error1 + error2);
}

int	check_file(char **content, int error, int i)
{
	while (content[i])
	{
		if (i == 0)
			error = check_textures(content[i], 0, 0, i);
		else if (i == 1)
			error = check_textures(content[i], 0, 0, i);
		else if (i == 2)
			error = check_textures(content[i], 0, 0, i);
		else if (i == 3)
			error = check_textures(content[i], 0, 0, i);
		else if (i == 5)
			error = check_colors(content[i], 0, i);
		else if (i == 6)
			error = check_colors(content[i], 0, i);
		if (error != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
