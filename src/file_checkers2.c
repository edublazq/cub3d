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
	if (i == 5 && ft_strncmp(line, "F ", 2))
		return (1);
	if (i == 6 && ft_strncmp(line, "C ", 2))
		return (1);
	i = 2;
	while (line[i] != '\n')
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != ',')
			return (1);
		i++;
	}
	return (0);
}

static int	check_numbers(char *line)
{
	char	**numbers;
	int		i;
	int		nmb;
	int		error;

	error = 0;
	numbers = ft_split(line, ',');
	i = 0;
	while (numbers[i])
	{
		nmb = ft_atoi(numbers[i]);
		if (i > 2 || nmb < 0 || nmb > 255)
			error = 1;
		i++;
	}
	free_argv(numbers);
	return (error);
}

int	check_colors(char *line, int error, int i)
{
	error = check_color_line(line, i);
	error = error + check_numbers(line);
	return (error);
}
