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
	int			len;
	int			new_len;
	int			j;
	char		*tmp;
	char		*new_line;
	char		**numbers;
	t_colors	colors;

	len = 0;
	new_len = 0;
	while (line[len])
	{
		if (line[len] == ' ')
			len++;
		len++;
		new_len++;
	}
	new_line = malloc(sizeof(char) * len);
	new_line = ft_strdup(line_with_no_spaces(line, new_line));
	numbers = ft_split(new_line, ',');
	tmp = new_line + 2;
	numbers = ft_split(tmp, ',');
	j = 0;
	while (numbers[j])
	{
		if (j == 0)
			colors.r = ft_atoi(numbers[j]);
		else if (j == 1)
			colors.g = ft_atoi(numbers[j]);
		else if (j == 2)
			colors.b = ft_atoi(numbers[j]);
		j++;
	}
	colors.a = 0xFF;
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

static int	parse_texture_line(t_map *map, char *line, int texture_index)
{
	char	*path;
	int		ret;

	path = extract_texture_path(line);
	if (!path)
		return (EXIT_FAILURE);
	ret = parse_texture(path, &map->textures[texture_index]);
	free(path);
	return (ret);
}

int	parse_header_line(t_map *map, char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (EXIT_SUCCESS);
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_texture_line(map, line, NORTH_TEXTURE));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_texture_line(map, line, SOUTH_TEXTURE));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_texture_line(map, line, WEST_TEXTURE));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_texture_line(map, line, EAST_TEXTURE));
	if (line[0] == 'F' && line[1] == ' ')
		map->floor_color = get_colors(line + 2);
	else if (line[0] == 'C' && line[1] == ' ')
		map->ceiling_color = get_colors(line + 2);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}