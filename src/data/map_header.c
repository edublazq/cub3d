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

static int	parse_texture(char *src, mlx_texture_t **dst)
{
	*dst = mlx_load_png(src);
	if (!*dst)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	*extract_texture_path(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (ft_substr(line, 3, len - 3));
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
		get_colors(line + 2, &map->floor_color);
	else if (line[0] == 'C' && line[1] == ' ')
		get_colors(line + 2, &map->ceiling_color);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
