/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checkers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:35:33 by edblazqu          #+#    #+#             */
/*   Updated: 2026/09/07 23:43:07 by jopelayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_color_line(char *line, int i)
{
	if (ft_strncmp(line, "F ", 2 && ft_strncmp(line, "C ", 2)))
		return (1);
	i = 2;
	while (line[i] != '\n')
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != ',' && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*line_with_no_spaces(char *line, char *new_line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			i++;
			continue;
		}
		line[i] = new_line[j];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

static int	check_numbers(char *line)
{
	char	**numbers;
	char	*new_line;
	int		i;
	int		len;
	int		new_len;
	int		nmb;
	int		error;

	error = 0;
	len = 2;
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
	i = 0;
	while (numbers[i])
	{
		nmb = ft_atoi(numbers[i]);
		if (i > 2 || nmb < 0 || nmb > 255)
			error = 1;
		i++;
	}
	free(new_line);
	free_matrix(numbers);
	return (error);
}

int	check_colors(char *line, int i)
{
	int error;

	error = 0;
	error = check_color_line(line, i);
	error = error + check_numbers(line);
	return (error);
}
