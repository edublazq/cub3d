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

static int	parse_map_content(t_map *map, char **content, char **aux, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < j)
	{
		if (parse_header_line(map, content[i]))
			return (EXIT_FAILURE);
		i++;
	}
	while (content[j])
	{
		aux[k] = content[j];
		k++;
		j++;
	}
	aux[k] = NULL;
	return (EXIT_SUCCESS);
}

int	get_data_for_map(t_map *map, char *file)
{
	char	**content;
	char	**aux;
	int		i;
	int		j;

	j = 0;
	content = read_file(file, NULL, 0, 0);

	if (!content)
		return (EXIT_FAILURE);
	i = 0;
	while (content[i])
		i++;
	while (content[j][0] != '1')
		j++;
	if (i < j)
		return (free_matrix(content), EXIT_FAILURE);
	aux = malloc(sizeof(char *) * (i - j + 1));
	if (!aux || parse_map_content(map, content, aux, j))
		return (free_matrix(content), free(aux), EXIT_FAILURE);
	map->grid = get_map(aux);
	if (!map->grid)
		return (free_matrix(content), free(aux), EXIT_FAILURE);
	map->height = i - j;
	map->width = ft_strlen(map->grid[0]);
	free_matrix(content);
	free(aux);
	return (EXIT_SUCCESS);
}
