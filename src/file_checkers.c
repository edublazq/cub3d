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

static int check_textures(char *line, int i)
{
    int len;
    int error1;
    int error2; 

    error1 = 0;
    error2 = 0;
    len = ft_strlen(line);
    if (i == 0)
    {
        error1 = ft_strncmp(line, "NO ./", 4);
        error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
    }
    else if (i == 1)
    {
        error1 = ft_strncmp(line, "SO ./", 4);
        error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
    }
    else if (i == 2)
    {
        error1 = ft_strncmp(line, "WE ./", 4);
        error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
    }
    else if (i == 3)
    {
        error1 = ft_strncmp(line, "EA ./", 4);
        error2 = ft_strncmp(&line[len - 5], ".xpm", 4);
    }
    return (error1 + error2);
}

static int check_colors(char *line, int i)
{
    int nmb;
    int error;
    char *tmp;
    char **numbers;

    error = 0;
    if (i == 5)
    {
        error = ft_strncmp(line, "F ", 2);
        i = 2;
        while(line[i])
        {
            if ((line[i] < '0' && line[i] > '9') && line[i] != ',')
            {
                error = 1;
                break ;
            }
            i++;
        }
    }
    else if (i == 6)
    {
        error = ft_strncmp(line, "C ", 2);
        i = 2;
        while(line[i])
        {
            if ((line[i] < '0' && line[i] > '9') && line[i] != ',')
            {
                error = 1;
                break ;
            }
            i++;
        }
        tmp = ft_substr(line, 2, i - 2);
        free(tmp);
    }
    numbers = ft_split(line, ',');
    i = 0;
    while (numbers[i])
    {
        nmb = ft_atoi(numbers[i]);
        if (i > 2 || nmb < 0 || nmb > 255)
            error = 1;
        i++;
    }
    return (free_argv(numbers), error);
}


int check_file(char **content)
{
	int i;
    int error;

    i = 0;
    error = 0;
    while (content[i])
    {
        if (i == 0)
            error = check_textures(content[i], i);
        else if (i == 1)
            error = check_textures(content[i], i);
        else if (i == 2)
            error = check_textures(content[i], i);
        else if (i == 3)
            error = check_textures(content[i], i);
        else if (i == 5)
            error = check_colors(content[i], i);
        else if (i == 6)
            error = check_colors(content[i], i);
        if (error != 0)
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}
