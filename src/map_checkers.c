/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:35:33 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/08 00:10:47 by jopelayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_characters(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\n' && line[i] != '\0'
			&& line[i] != 'N' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != 'S')
			return (EXIT_FAILURE);
		if (!ft_strcmp(line, "\n"))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(char **content, size_t longest, int i, int j)
{
	size_t	width;

	while (content[i])
	{
		if (check_map_characters(content[i]))
			return (EXIT_FAILURE);
		width = ft_strlen(content[i]);
		if (width >= 2 && width - 2 > longest)
			longest = width - 2;
		i++;
	}
	return (build_and_validate_map(content, i, j, longest));
}
