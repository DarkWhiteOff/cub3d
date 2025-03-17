#include "../includes/cub3d.h"

void	is_epc(t_main *main, int i, int j, t_pxy *p_pos)
{
	if (main->map.grid[i][j] == 'N' || main->map.grid[i][j] == 'S' || main->map.grid[i][j] == 'W' || main->map.grid[i][j] == 'E')
	{
		main->map.player_pos++;
		p_pos->x = j;
		p_pos->y = i;
		if (main->map.grid[i][j] == 'N')
			main->ray.ray_angle = 270.0;
		if (main->map.grid[i][j] == 'S')
			main->ray.ray_angle = 90.0;
		if (main->map.grid[i][j] == 'W')
			main->ray.ray_angle = 180.0;
		if (main->map.grid[i][j] == 'E')
			main->ray.ray_angle = 0.0;
	}
}

int	check_other_char(t_map *map, int y, int x)
{
	if (map->grid[y][x] != 'N' && map->grid[y][x] != 'S' && map->grid[y][x] != 'W' && map->grid[y][x] != 'E' && map->grid[y][x] != '0' && map->grid[y][x] != '1')
		return (1);
	return (0);
}

void	check_epc(t_main *main, t_pxy *p_pos)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < main->map.h - 1)
	{
		while (main->map.grid[i][j] != '\0')
		{
			is_epc(main, i, j, p_pos);
			if (check_other_char(&main->map, i, j) == 1)
			{
				free_grids(&main->map);
				exit (ft_printf("Error\nMap contains unrecognized character.\n"));
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (main->map.player_pos != 1)
	{
		free_grids(&main->map);
		exit (ft_printf("Error\nNo player position.\n"));
	}
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
	line = get_next_line(main->map.fd);
	while (main->tex.map_start--)
	{
		free(line);
		line = get_next_line(main->map.fd);
	}
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
		line = get_next_line(main->map.fd);
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
