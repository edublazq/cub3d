/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:00:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/02 20:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_colors	get_colors(char *line)
{
	int			j;
	char		*tmp;
	char		**numbers;
	t_colors	colors;

	tmp = line + 2;
	numbers = ft_split(tmp, ',');
	j = 0;
	while (numbers[j])
	{
		if (j == 0)
			colors.one = ft_atoi(numbers[j]);
		else if (j == 1)
			colors.two = ft_atoi(numbers[j]);
		else if (j == 2)
			colors.three = ft_atoi(numbers[j]);
		j++;
	}
	free_matrix(numbers);
	return (colors);
}

static int	parse_texture(char *src, mlx_texture_t *dst)
{
	dst = mlx_load_png(src);
	if (!dst)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//WORKING IN PROGESS

int	parse_header_line(t_map *map, char **content, int i)
{
	char	*tmp;

	if (i == 0)
		return (parse_texture());
	if (i == 1)
		return (parse_texture());
	if (i == 2)
		return (parse_texture());
	if (i == 3)
		return (parse_texture());
	if (i == 5 || i == 6)
	{
		tmp = ft_strdup(content[i]);
		if (!tmp)
			return (EXIT_FAILURE);
		tmp[ft_strlen(tmp) - 1] = '\0';
		if (i == 5)
			map->floor_color = get_colors(tmp);
		else
			map->ceiling_color = get_colors(tmp);
		free(tmp);
	}
	return (EXIT_SUCCESS);
}
