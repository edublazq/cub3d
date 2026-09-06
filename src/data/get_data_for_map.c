/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_for_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:44:30 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_map_content(t_map *map, char **content, char **aux, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (parse_header_line(map, content, i))
			return (EXIT_FAILURE);
		if (i > 7)
			aux[i - 8] = content[i];
		i++;
	}
	aux[i - 8] = NULL;
	return (EXIT_SUCCESS);
}

int	get_data_for_map(t_map *map, char *file)
{
	char	**content;
	char	**aux;
	int		i;

	content = read_file(file);
	if (!content)
		return (EXIT_FAILURE);
	i = 0;
	while (content[i])
		i++;
	aux = malloc(sizeof(char *) * (i - 8 + 1));
	if (!aux || parse_map_content(map, content, aux, i))
		return (free_matrix(content), free(aux), EXIT_FAILURE);
	map->grid = get_map(aux);
	if (!map->grid)
		return (free_matrix(content), free(aux), EXIT_FAILURE);
	map->height = i - 8;
	map->width = ft_strlen(map->grid[0]);
	free_matrix(content);
	free(aux);
	return (EXIT_SUCCESS);
}
