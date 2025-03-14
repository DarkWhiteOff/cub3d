#include "../includes/cub3d.h"

void	is_epc(t_map *map, int i, int j, t_pxy *p_pos)
{
	if (map->grid[i][j] == 'P')
	{
		map->player_pos++;
		p_pos->x = j;
		p_pos->y = i;
	}
}

void	check_epc(t_map *map, t_pxy *p_pos)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < map->h - 1)
	{
		while (map->grid[i][j] != '\0')
		{
			is_epc(map, i, j, p_pos);
			if (check_map_limits_epc(map, i, j) == 0)
			{
				free_grids(map);
				exit (ft_printf("Error\nMap contains unrecognized character.\n"));
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (map->player_pos != 1)
	{
		free_grids(map);
		exit (ft_printf("Error\nVerify your player position.\n"));
	}
}

void	check_path(t_map *map, int x, int y)
{
	if (map->grid[y][x] == '1' || map->highlight_grid[y][x] == '1'
		|| x < 0 || y < 0 || x > map->w || y > map->h)
		return ;
	map->highlight_grid[y][x] = '1';
	check_path(map, x - 1, y);
	check_path(map, x + 1, y);
	check_path(map, x, y - 1);
	check_path(map, x, y + 1);
	return ;
}

void	allocate_grids(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->grid = (char **)malloc(sizeof(char *) * map->h + 1);
	map->highlight_grid = (char **)malloc(sizeof(char *) * map->h + 1);
	while (i < map->h)
	{
		map->grid[i] = (char *)malloc(sizeof(char) * map->w + 1);
		map->highlight_grid[i] = (char *)malloc(sizeof(char) * map->w + 1);
		i++;
	}
	i = 0;
	while (i < map->h)
	{
		while (j < map->w)
		{
			map->highlight_grid[i][j] = '0';
			j++;
		}
		map->highlight_grid[i][j] = '\0';
		i++;
		j = 0;
	}
}

void	grid_init(t_main *main)
{
	char	*line;
	int		j;
	int		i;

	i = 0;
	j = 0;
	main->map.fd = open(main->map.path, O_RDONLY);
	check_fd_error(main);
	line = get_next_line(main->map.fd, &main->map);
	allocate_grids(&main->map);
	while (i < main->map.h)
	{
		while (line[j] && line[j] != '\n')
		{
			main->map.grid[i][j] = line[j];
			j++;
		}
		main->map.grid[i++][j] = '\0';
		j = 0;
		free(line);
		line = get_next_line(main->map.fd, &main->map);
	}
	close(main->map.fd);
}

void	free_grids(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->h)
	{
		free(map->grid[i]);
		free(map->highlight_grid[i]);
		i++;
	}
	free(map->grid);
	free(map->highlight_grid);
}
