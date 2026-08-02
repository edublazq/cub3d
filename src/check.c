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

char **read_file(char *file)
{
	int i;
	int fd;
	char *line;
	char **content;

	i = 0;
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
	}
	content = malloc(sizeof(char *) * (i + 1));
	close(fd);
	fd = open(file, O_RDONLY);
	i = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		content[i] = NULL;
		content[i] = line;
		i++;
	}
	content[i] = NULL;
	close (fd);
	return (content);
}

int	check_arg(int ac, char **av)
{
	int	len;
	char **file_content;

	if (ac != 2)
		return (EXIT_FAILURE);
	len = ft_strlen(av[1]);
	if (len <= 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		printf("%s\n", "File's name is not correct.");
		return (EXIT_FAILURE);
	}
	file_content = read_file(av[1]);
	if (check_file(file_content))
	{
		printf("%s\n", "File structure is not correct.");
		/* printf() de la estructura correcta */
		return (EXIT_FAILURE);
	}
	if (check_map(file_content))
	{
		printf("%s\n", "Map structure is not correct.");
		/* printf() de la estructura correcta */
		return (EXIT_FAILURE);
	}
	printf("%s", file_content[0]);
	free_argv(file_content);
	return (EXIT_SUCCESS);
}

