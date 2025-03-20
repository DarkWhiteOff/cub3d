#include "../includes/cub3d.h"

void	check_walls1(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->map.diff_w[0])
	{
		while (main->map.grid[0][i] == ' ')
			i++;
		if (main->map.grid[0][i] != '1' && (main->map.grid[0][i] != ' ' && i < main->map.diff_w[0]))
		{
			free(main->map.diff_w);
			free_textures(main);
			free_grids(main);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
	i = 0;
	while (i < main->map.diff_w[main->map.h - 1])
	{
		while (main->map.grid[0][i] == ' ')
			i++;
		if (main->map.grid[0][i] != '1' && (main->map.grid[0][i] != ' ' && i < main->map.diff_w[0]))
		{
			free(main->map.diff_w);
			free_textures(main);
			free_grids(main);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
}

void	check_walls2(t_main *main)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	while (i < main->map.h - 1)
	{
		while (main->map.grid[i][j] == ' ')
			j++;
		if (main->map.grid[i][j] != '1')
		{
			free(main->map.diff_w);
			free_textures(main);
			free_grids(main);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		if (main->map.grid[i][main->map.diff_w[i] - 1] != '1')
		{
			free(main->map.diff_w);
			free_textures(main);
			free_grids(main);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		j = 0;
		i++;
	}
}

void	check_path(t_main *main, int x, int y)
{
	if (main->map.grid[y][x] == ' ')
	{
		free(main->map.diff_w);
		free_textures(main);
		exit(printf("Error\nMap not closed.\n"));
	}
	if (main->map.grid[y][x] == '1' || main->map.highlight_grid[y][x] == '1' || x < 0 || y < 0 || x > main->map.diff_w[y] || y > main->map.h)
		return ;
	main->map.highlight_grid[y][x] = '1';
	check_path(main, x - 1, y);
	check_path(main, x + 1, y);
	check_path(main, x, y - 1);
	check_path(main, x, y + 1);
	return ;
}
