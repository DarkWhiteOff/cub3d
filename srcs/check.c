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

void get_diff_width(t_main *main)
{
	int fd;
	int ok;
	char	*l;
	int i = 0;

	fd = open(main->map.path, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
	l = get_next_line(fd);
	ok = main->tex.map_start;
	while (ok--)
	{
		free(l);
		l = get_next_line(fd);
	}
	while (l)
	{
		main->map.diff_w[i++] = strlenmap(l);
		free(l);
		l = get_next_line(main->fdtest);
	}
	close(fd);
	main->map.diff_w[i] = -1;
}

int	check_w(int *array)
{
	int i = 0;
	while (array[i] != -1)
	{
		if (array[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(t_main *main)
{
	char	*l;

	l = get_next_line(main->fdtest);
	// while (ft_strncmp(l, "", 42) == 0)
	// {
	// 	free(l);
	// 	get_next_line(main->fdtest);
	// }
	empty_line_check(l, main->fdtest);
	while (l)
	{
		main->map.h++;
		empty_line_check(l, main->fdtest);
		free(l);
		l = get_next_line(main->fdtest);
	}
	close(main->fdtest);
	main->map.diff_w = (int *)malloc(sizeof(int) * (main->map.h + 1));
	get_diff_width(main);
	if (check_w(main->map.diff_w) == 0 || main->map.h == 0)
		exit (ft_printf("Error\nMap not rectangular / nothing in it.\n"));
}

void	check_walls1(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->diff_w[0])
	{
		while (map->grid[0][i] == ' ')
			i++;
		if (map->grid[0][i] != '1' && (map->grid[0][i] != ' ' && i < map->diff_w[0]))
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
	i = 0;
	while (i < map->diff_w[map->h - 1])
	{
		while (map->grid[0][i] == ' ')
			i++;
		if (map->grid[0][i] != '1' && (map->grid[0][i] != ' ' && i < map->diff_w[0]))
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
	int j;

	i = 1;
	j = 0;
	while (i < map->h - 1)
	{
		while (map->grid[i][j] == ' ')
			j++;
		if (map->grid[i][j] != '1')
		{
			printf("hi : %d | j : %d\n", i, j);
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		if (map->grid[i][map->diff_w[i] - 1] != '1')
		{
			printf("bi : %d | j : %d\n", i, map->diff_w[i] - 1);
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		j = 0;
		i++;
	}
}

void	check_path(t_map *map, int x, int y)
{
	if (map->grid[y][x] == ' ')
		exit(printf("FUCK\n"));
	if (map->grid[y][x] == '1' || map->highlight_grid[y][x] == '1'
		|| x < 0 || y < 0 || x > map->diff_w[y] || y > map->h)
		return ;
	map->highlight_grid[y][x] = '1';
	check_path(map, x - 1, y);
	check_path(map, x + 1, y);
	check_path(map, x, y - 1);
	check_path(map, x, y + 1);
	return ;
}
