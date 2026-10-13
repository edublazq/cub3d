/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 00:00:00 by edblazqu          #+#    #+#             */
/*   Updated: 2026/10/13 00:00:01 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_colors(t_colors *c)
{
	c->r = 0;
	c->g = 0;
	c->b = 0;
	c->a = 0xFF;
	c->rgba = 0;
}

static void	fill_colors(t_colors *c, char **numbers)
{
	int	j;

	j = 0;
	while (numbers[j])
	{
		if (j == 0)
			c->r = ft_atoi(numbers[j]);
		else if (j == 1)
			c->g = ft_atoi(numbers[j]);
		else if (j == 2)
			c->b = ft_atoi(numbers[j]);
		j++;
	}
	c->rgba = ((uint32_t)c->r << 24) | (c->g << 16) | (c->b << 8) | c->a;
}

void	get_colors(char *line, t_colors *out)
{
	char	*new_line;
	char	**numbers;

	init_colors(out);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return ;
	line_with_only_numbers(line, new_line);
	numbers = ft_split(new_line, ',');
	fill_colors(out, numbers);
	free(new_line);
	free_matrix(numbers);
}
