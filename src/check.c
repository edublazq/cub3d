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

static void	print_error(int error)
{
	printf("\033[1;91mInput is invalid.\n");
	printf("File has to be a '.cub' and readable.\n");
	if (error == 1)
	{
		printf("It has to follow the exact next structure:\n\033[0;39m");
		printf("-------------------------------------\n");
		printf("NO /path_to_the_north_texture.xpm\n");
		printf("SO /path_to_the_south_texture.xpm\n");
		printf("WE /path_to_the_west_texture.xpm\n");
		printf("EA /path_to_the_east_texture.xpm\n");
		printf("\n");
		printf("F nmb,nmb,nmb\nC nmb,nmb,nmb\n");
		printf("\n");
		printf("Map will follow.\n");
		printf("\033[1;91m'.png' files have to be readable ");
		printf("and numbers have to go from 0 to 255.\n");
	}
	if (error == 2)
	{
		printf("Maps only contain '0', '1' and one player marked as E/W/S/N.\n");
		printf("Open maps will not be tolerated.\n");
	}
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
	int		j;
	int		len;
	char	**file_content;

	j = 0;
	if (ac != 2)
		return (EXIT_FAILURE);
	len = ft_strlen(av[1]);
	if (len <= 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		printf("%s\n", "\033[1;91mFile's name is not correct.");
		return (EXIT_FAILURE);
	}
	file_content = read_file(av[1], NULL, 0, 0);
	while (file_content[j][0] != '1')
		j++;
	if (file_content == NULL || check_file(file_content, 0, 0)
		|| check_map(file_content, 0, j, j))
	{
		if (check_file(file_content, 0, 0))
			print_error(TEXTURES_AND_COLORS);
		else if (check_map(file_content, 0, j, j))
			print_error(MAP);
		return (free_matrix(file_content), EXIT_FAILURE);
	}
	return (free_matrix(file_content), EXIT_SUCCESS);
}
