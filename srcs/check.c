#include "../includes/cub3d.h"

void	get_infos(t_main *main)
{
	char	*line;
	int NO = 0;
	int SO = 0;
	int WE = 0;
	int EA = 0;

	main->fdtest = open(main->map.path, O_RDONLY);
	if (main->fdtest < 0 || read(main->fdtest, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
	line = get_next_line(main->fdtest);
	while (line)
	{
		main->tex.map_start++;
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			main->tex.NO = ft_substr(line, 3, ft_strlen(line) - 3);
			NO = 1;
		}
		if (ft_strncmp(line, "SO ", 3) == 0)
		{
			main->tex.SO = ft_substr(line, 3, ft_strlen(line) - 3);
			SO = 1;
		}
			if (ft_strncmp(line, "WE ", 3) == 0)
		{
			main->tex.WE = ft_substr(line, 3, ft_strlen(line) - 3);
			WE = 1;
		}
		if (ft_strncmp(line, "EA ", 3) == 0)
		{
			main->tex.EA = ft_substr(line, 3, ft_strlen(line) - 3);
			EA = 1;
		}
		// if (ft_strncmp(l, "F ", 2))
		// if (ft_strncmp(l, "C ", 2))
		free(line);
		if (NO == 1 && SO == 1 && WE == 1 && EA == 1)
			break ;
		line = get_next_line(main->fdtest);
	}
	main->tex.map_start++;
	// if (NO != 1 && SO != 1 && WE != 1 && EA != 1)
	// 	ft_printf("Error\nTextures missing.\n");
}

void	empty_line_check(char *line, int fd)
{
	if (line == NULL)
		exit (ft_printf("Error\nYou entered an empty map !\n"));
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		close(fd);
		exit (ft_printf("Error\nYour map has one or more empty lines.\n"));
	}
}

void	parse_map(t_main *main)
{
	char	*l;
	int		line_samelen;

	line_samelen = 0;
	l = get_next_line(main->fdtest);
	while (ft_strncmp(l, "", 42) == 0)
	{
		free(l);
		get_next_line(main->fdtest);
	}
	empty_line_check(l, main->fdtest);
	main->map.w = strlenmap(l);
	while (l)
	{
		if (strlenmap(l) != main->map.w)
			line_samelen = 1;
		main->map.h++;
		empty_line_check(l, main->fdtest);
		free(l);
		l = get_next_line(main->fdtest);
	}
	close(main->fdtest);
	if (main->map.w == main->map.h || main->map.w == 0 || main->map.h == 0 || line_samelen == 1)
		exit (ft_printf("Error\nMap not rectangular / nothing in it.\n"));
}

void	check_walls1(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->w)
	{
		if (map->grid[0][i] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
	i = 0;
	while (i < map->w)
	{
		if (map->grid[map->h - 1][i] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
}

void	check_walls2(t_map *map)
{
	int	i;

	i = 1;
	while (i < map->h - 1)
	{
		if (map->grid[i][0] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		if (map->grid[i][map->w - 1] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
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
