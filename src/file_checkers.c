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

static int	is_header_line(const char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (1);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
		return (1);
	return (0);
}

int	get_map_start(char **content)
{
	int	i;

	i = 0;
	while (content[i] && is_header_line(content[i]))
		i++;
	return (i);
}

int	check_file(char **content, int error, int i)
{
	int	max;
	int	final_sum;
	int	header_end;

	max = 0;
	final_sum = 0;
	if (!content)
		return (EXIT_FAILURE);
	header_end = get_map_start(content);
	while (i < header_end)
	{
		if (content[i][0] == '\n')
		{
			i++;
			continue;
		}
		if (check_textures(content[i]) && check_colors(content[i], 0))
			error++;
		max++;
		final_sum = final_sum + (int)content[i][0];
		i++;
	}
	if (max > 6 || final_sum != ('N' + 'S' + 'E' + 'W' + 'F' + 'C'))
		error++;
	if (error != 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
