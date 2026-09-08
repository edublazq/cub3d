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

static void	print_error(void)
{
	printf("\033[1;91mInput is invalid.\n");
	printf("File has to be a '.cub' and readable.\n");
	printf("It has to follow the exact next structure:\n\033[0;39m");
	printf("-------------------------------------\n");
	printf("NO ./path_to_the_north_texture.xpm\n");
	printf("SO ./path_to_the_south_texture.xpm\n");
	printf("WE ./path_to_the_west_texture.xpm\n");
	printf("EA ./path_to_the_east_texture.xpm\n");
	printf("\n");
	printf("F nmb,nmb,nmb\nC nmb,nmb,nmb\n");
	printf("\n");
	printf("Map structure will follow.\n");
	printf("-------------------------------------\n");
	printf("\033[1;91m'.xpm' files have to be readable ");
	printf("and numbers have to go from 0 to 255.\n");
	printf("Maps only contain '0', '1' and one player marked as E/W/S/N.\n");
	printf("Open maps will not be tolerated.\n\033[0;39m");
}

static int	count_lines(char *line, int fd, int i)
{
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	return (i);
}

char	**read_file(char *file, char *line, int fd, int i)
{
	char	**content;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = count_lines(NULL, fd, i);
	content = malloc(sizeof(char *) * (i + 1));
	if (!content)
		return (NULL);
	close(fd);
	fd = open(file, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		content[i] = line;
		i++;
	}
	content[i] = NULL;
	close (fd);
	return (content);
}

int	check_arg(int ac, char **av)
{
	int		len;
	char	**file_content;

	if (ac != 2)
		return (EXIT_FAILURE);
	len = ft_strlen(av[1]);
	if (len <= 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		printf("%s\n", "File's name is not correct.");
		return (EXIT_FAILURE);
	}
	file_content = read_file(av[1], NULL, 0, 0);
	if (file_content == NULL || check_file(file_content, 0, 0)
		|| check_map(file_content, 0, 8))
	{
		print_error();
		return (free_argv(file_content), EXIT_FAILURE);
	}
	return (free_argv(file_content), EXIT_SUCCESS);
}
