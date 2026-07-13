#include "cub3d.h"

#define COLS 10
#define ROWS 10

t_map	try_map()
{
	t_map	map;

	map.cols = COLS;
	map.rows = ROWS;
	map.grid = malloc(map.cols);
	for (int i = 0; i < map.cols; i++)
		map.grid[i] = malloc(map.rows);
	for (int i = 1; i < map.cols - 1; i++)
	{
		for (int j = 1; j < map.rows - 1; j++)
			map.grid[i][j] = '0';
	}
	map.grid[3][3] = 'N';
	for (int i = 0; i < map.cols; i++)
	{
		map.grid[i][0] = '1';
		map.grid[i][map.cols - 1] = '1';
	}
	for (int j = 0; j < map.rows; j++)
	{
		map.grid[0][j] = '1';
		map.grid[map.rows - 1][0] = '1';
	}
	return (map);
}
