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

static int	parse_texture(char *src, mlx_texture_t **dst)
{
	*dst = mlx_load_png(src);
	if (!*dst)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	*extract_texture_path(char *line)
{
	return (ft_substr(line, 3, ft_strlen(line) - 4));
}

static int	parse_texture_line(t_map *map, char *line, int i)
{
	char	*path;
	int		ret;

	path = extract_texture_path(line);
	if (!path)
		return (EXIT_FAILURE);
	if (i == 0)
		ret = parse_texture(path, &map->textures[NORTH_TEXTURE]);
	else if (i == 1)
		ret = parse_texture(path, &map->textures[SOUTH_TEXTURE]);
	else if (i == 2)
		ret = parse_texture(path, &map->textures[WEST_TEXTURE]);
	else
		ret = parse_texture(path, &map->textures[EAST_TEXTURE]);
	free(path);
	return (ret);
}

int	parse_header_line(t_map *map, char **content, int i)
{
	char	*tmp;

	if (i >= 0 && i <= 3)
		return (parse_texture_line(map, content[i], i));
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
