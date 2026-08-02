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

static int	check_map_characters(const char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n' && line[i] != '\0'
            && line[i] != 'N' && line[i] != 'E' && line[i] != 'W' && line[i] != 'S')
            return (EXIT_FAILURE);
        i++;
    }
	return (EXIT_SUCCESS);
}

static int count_players(char **content)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 8;
    while (content[i])
    {
        j = 0;
        while(content[i][j])
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

static char *map_rectangulizer(char *line, int longest)
{
    int i;
    char *map;

    i = 0;
    map = malloc(sizeof(char) * (longest + 1));
    while (line[i] != '\n')
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

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_void(char c)
{
	return (c == ' ' || c == '-' || c == '\0');
}

static int open_map(char **map, int max)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < max)
    {
        while (x < max)
        {
            if (is_walkable(map[y][x]))
            {
                if (is_void(map[y - 1][x]) || is_void(map[y + 1][x]) || is_void(map[y][x - 1]) || is_void(map[y][x + 1]))
                    return (EXIT_FAILURE);
            }
            x++;    
        }
        y++;
    }
    return (EXIT_SUCCESS);
}


int	check_map(char **content)
{
    int i;
    size_t longest;
    char **map;

    longest = 0;
    i = 8;
    while (content[i])
    {
        if (check_map_characters(content[i]))
            return (EXIT_FAILURE);
        if (ft_strlen(content[i]) > longest)
            longest = ft_strlen(content[i]) - 2;
        i++;
    }
    if (count_players(content))
        return (EXIT_FAILURE);
    map = malloc(sizeof(char *) * (i - 8 + 1));
    i = 8;
    while (content[i])
    {
        map[i - 8] = NULL;
        if (ft_strlen(content[i]) - 2 <= longest)
            map[i - 8] = map_rectangulizer(content[i], longest);
        i++;
    }
    map[i - 8] = NULL;
    if (open_map(map, longest))
        return (EXIT_FAILURE);
    free_argv(map);
    return (EXIT_SUCCESS);
}