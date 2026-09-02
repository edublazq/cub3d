/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:00:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*map_rectangulizer(char *line, char *map, int longest)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		map[i] = line[i];
		i++;
	}
	while (i <= longest - 1)
	{
		map[i] = '-';
		i++;
	}
	map[i] = '\0';
	return (map);
}

static size_t	longest_line(char **aux)
{
	int		i;
	size_t	longest;

	i = 0;
	longest = 0;
	while (aux[i])
	{
		if (ft_strlen(aux[i]) - 1 > longest)
			longest = ft_strlen(aux[i]) - 1;
		i++;
	}
	return (longest);
}

char	**get_map(char **aux)
{
	int		i;
	char	**map;
	size_t	longest;

	i = 0;
	while (aux[i])
		i++;
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (NULL);
	longest = longest_line(aux);
	i = 0;
	while (aux[i])
	{
		map[i] = malloc(sizeof(char) * (longest + 2));
		if (!map[i])
			return (free_argv(map), NULL);
		if (ft_strlen(aux[i]) - 2 <= longest)
			map[i] = map_rectangulizer(aux[i], map[i], longest);
		i++;
	}
	map[i] = NULL;
	return (map);
}
