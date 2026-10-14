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

int	check_textures(char *line)
{
	int	len;
	int	error;

	error = 0;
	len = ft_strlen(line);
	if (ft_strncmp(line, "NO ", 3) && ft_strncmp(line, "SO ", 3)
		&& ft_strncmp(line, "WE ", 3) && ft_strncmp(line, "EA ", 3))
	{
		error++;
	}
	if (len < 5 || ft_strncmp(&line[len - 5], ".png", 4))
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
	int	header_end;

	if (!content)
		return (EXIT_FAILURE);
	header_end = get_map_start(content);
	error = error + tally_headers(content, header_end, i);
	if (error != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
