/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checkers3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 00:00:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/10/13 00:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	classify_header_line(char *line, int *count, int *error)
{
	if (!ft_strncmp(line, "NO ", 3))
		count[0]++;
	else if (!ft_strncmp(line, "SO ", 3))
		count[1]++;
	else if (!ft_strncmp(line, "WE ", 3))
		count[2]++;
	else if (!ft_strncmp(line, "EA ", 3))
		count[3]++;
	else if (line[0] == 'F' && line[1] == ' ')
		count[4]++;
	else if (line[0] == 'C' && line[1] == ' ')
		count[5]++;
	else
		(*error)++;
}

static int	count_duplicates(int *count)
{
	int	k;
	int	error;

	k = 0;
	error = 0;
	while (k < 6)
	{
		if (count[k] != 1)
			error++;
		k++;
	}
	return (error);
}

int	tally_headers(char **content, int header_end, int start)
{
	int	count[6];
	int	k;
	int	error;

	k = 0;
	while (k < 6)
		count[k++] = 0;
	error = 0;
	while (start < header_end)
	{
		if (content[start][0] != '\n')
		{
			if (check_textures(content[start])
				&& check_colors(content[start], 0))
				error++;
			classify_header_line(content[start], count, &error);
		}
		start++;
	}
	return (error + count_duplicates(count));
}
