/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:35:33 by edblazqu          #+#    #+#             */
/*   Updated: 2026/05/30 15:35:34 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_colors    get_colors(char *line)
{
    int j;
    char *tmp;
    char **numbers;
    t_colors colors;

    j = ft_strlen(line);
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
    free_argv(numbers);
    return (colors);
}

static char *map_rectangulizer(char *line, char *map, int longest)
{
    int i;

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

static char **get_map(char **aux)
{
    int i;
    char **map;
    size_t longest;

    longest = 0;
    i = 0;
    while (aux[i])
        i++;
    map = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (aux[i])
    {
        if (ft_strlen(aux[i]) - 1 > longest)
            longest = ft_strlen(aux[i]) - 1;
        i++;
    }
    i = 0;
    while (aux[i])
    {
        map[i] = malloc(sizeof(char) * (longest + 2));
        if (ft_strlen(aux[i]) - 2 <= longest)
            map[i] = map_rectangulizer(aux[i], map[i], longest);
        i++;
    }
    map[i] = NULL;
    return (map);
}

void    get_data_for_map(t_map *map, char *file)
{
    int i;
    char *tmp;
    char **content;
    char **aux;

    map->textures = malloc(sizeof(t_texture));
    i = 0;
    content = read_file(file);
    while (content[i])
        i++;
    aux = malloc(sizeof(char *) * (i - 8 + 1));
    i = 0;
    while (content[i])
    {
        tmp = ft_strdup(content[i]);
        tmp[ft_strlen(tmp) - 1] = '\0';
        if (i == 0)
            map->textures->no = ft_strchr(tmp, '.');
        else if (i == 1)
            map->textures->so = ft_strchr(tmp, '.');
        else if (i == 2)
            map->textures->we = ft_strchr(tmp, '.');
        else if (i == 3)
            map->textures->ea = ft_strchr(tmp, '.');
        else if (i == 5)
            map->floor_color = get_colors(tmp);
        else if (i == 6)
            map->ceiling_color = get_colors(tmp);
        else if (i > 7) 
            aux[i - 8] = content[i];
        free(tmp);
        i++;
    }
    aux[i - 8] = NULL;
    map->grid = get_map(aux);
    map->height = i - 8;
    map->width = ft_strlen(map->grid[0]);
    free_argv(content);
    free(aux);
}

void    get_data_for_player(t_player *player, t_map *map)
{
    int i;
    int j;
    char c;

    i = 0;
    while ((map->grid)[i])
    {
        j = 0;
        while ((map->grid)[i][j])
        {
            c = map->grid[i][j];
            if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
            {
                if (c == 'N')
                {
                    (player->orientation).x = 0;
                    (player->orientation).y = -1;
                }
                else if (c == 'S')
                {
                    (player->orientation).x = 0;
                    (player->orientation).y = 1;
                }
                else if (c == 'E')
                {
                    (player->orientation).x = -1;
                    (player->orientation).y = 0;
                }
                else if (c == 'W')
                {
                    (player->orientation).x = 1;
                    (player->orientation).y = 0;
                }
                (player->pos).x = j + 0.5;
                (player->pos).y = i + 0.5;
                map->grid[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    player->fov = 60;
    player->plane = vec2_scale(vec2_perp(player->orientation),
            tan((player->fov * PI / 180.0) / 2.0));
}
