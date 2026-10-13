/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 00:00:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/10/13 00:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_players(char **content, int max)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = max;
	while (content[i])
	{
		j = 0;
		while (content[i][j])
		{
			if (content[i][j] == 'N' || content[i][j] == 'E'
					|| content[i][j] == 'W' || content[i][j] == 'S')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	*map_rectangulizer(char *line, char *map, int longest)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		map[i] = line[i];
		i++;
	}
	while (i <= longest)
	{
		map[i] = '-';
		i++;
	}
	map[i] = '\n';
	map[i + 1] = '\0';
	return (map);
}

static int	open_map(char **map, int max)
{
	int	x;
	int	y;

	y = max;
	while (map[y])
	{
		x = 0;
		while (is_walkable(map[y][x]) == 1 || map[y][x] == '1'
			|| map[y][x] == ' ')
		{
			if (is_walkable(map[y][x]))
			{
				if (y == max || !map[y + 1] || x == 0
					|| is_void(map[y - 1][x]) || is_void(map[y + 1][x])
					|| is_void(map[y][x - 1]) || is_void(map[y][x + 1]))
					return (EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	build_and_validate_map(char **content, int end, int j, size_t longest)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (end - j + 1));
	if (!map)
		return (EXIT_FAILURE);
	i = j;
	while (content[i])
	{
		map[i - j] = malloc(sizeof(char) * (longest + 3));
		if (!map[i - j])
			return (free_matrix(map), EXIT_FAILURE);
		if (ft_strlen(content[i]) - 2 <= longest)
			map[i - j] = map_rectangulizer(content[i], map[i - j], longest);
		i++;
	}
	map[i - j] = NULL;
	if (count_players(map, 0) || open_map(map, 0))
		return (free_matrix(map), EXIT_FAILURE);
	return (free_matrix(map), EXIT_SUCCESS);
}
