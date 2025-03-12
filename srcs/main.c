#include "../includes/cub3d.h"

int	*copy_map(t_map *map)
{
	int x = 0;
	int y = 0;
	int i = 0;

	int	*_map = malloc(map->w * map->h * sizeof(int));
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (map->grid[y][x] == '1')
				_map[i++] = 1;
			else
				_map[i++] = 0;
			x++;
		}
		y++;
	}
	return _map;
}

void	vars_init(t_map *map, char *map_path)
{
	map->path = map_path;
	map->h = 0;
	map->w = 0;
	map->ex = 0;
	map->pos = 0;
	map->coll = 0;
	map->exit_acc = 0;
	map->coll_acc = 0;
	map->player_on_exit = 0;
	map->moves = 0;
	map->sc_s.x = 0;
	map->sc_s.y = 0;
	map->z = 0;
	map->q = 0;
	map->s = 0;
	map->d = 0;
	map->left = 0;
	map->right = 0;
	map->pixel_pos_x = 0;
	map->pixel_pos_y = 0;
	map->pos_a = 180;
	map->pos_dx = cos(map->pos_a) * 5;
	map->pos_dy = sin(map->pos_a) * 5;
}

void	save_pos(t_pxy *x_pos, int j, int i)
{
	x_pos->x = j;
	x_pos->y = i;
}

void	check_fd_error(t_main *main)
{
	if (main->map.fd < 0 || read(main->map.fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
}

int	strlenmap(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (i > map->sc_s.x / 48)
	{
		free(line);
		exit (ft_printf("Error\nYour screen is too small for this map !"));
	}
	return (i);
}

void	get_screen_size(t_map *map)
{
	void	*mlxptr;

	mlxptr = mlx_init();
	if (!mlxptr)
	{
		free(mlxptr);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	mlx_get_screen_size(mlxptr, &map->sc_s.x, &map->sc_s.y);
	mlx_destroy_display(mlxptr);
	free(mlxptr);
}

void	checks_inits(t_main *main)
{
	get_screen_size(&main->map);
	parse_map(&main->map);
	grid_init(main);
	check_walls1(&main->map);
	check_walls2(&main->map);
	check_epc(&main->map, &main->p_pos);
	main->map.pixel_pos_x = main->p_pos.x * 48;
	main->map.pixel_pos_y = main->p_pos.y * 48;
	main->map.grid[main->p_pos.y][main->p_pos.x] = '0';
	check_path(&main->map, main->p_pos.x, main->p_pos.y);
}

int	check_map_name(char *map_name)
{
	int	i;

	i = 0;
	while (map_name[i] != '\0')
		i++;
	if (map_name[i - 1] == 'r' && map_name[i - 2] == 'e'
		&& map_name[i - 3] == 'b' && map_name[i - 4] == '.'
		&& (map_name[i - 5] != '/' && map_name[i - 5] != 0))
		return (0);
	return (1);
}

void	render_init(t_main *main)
{
	main->mlx_p = mlx_init();
	if (!main->mlx_p)
	{
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->mlx_win = mlx_new_window(main->mlx_p,
		(main->map.w * 48) * 2, main->map.h * 48, "cub3d");
	if (!main->mlx_win)
	{
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		free_grids(&main->map);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->img = mlx_new_image(main->mlx_p, (main->map.w * 48) * 2, main->map.h * 48);
	if (!main->img)
	{
		mlx_destroy_window(main->mlx_p, main->mlx_win);
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		free_grids(&main->map);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->addr = mlx_get_data_addr(main->img, &main->b, &main->ls, &main->end);
}

int	main(int argc, char *argv[])
{
	t_main	main;

	if (argc != 2)
		return (ft_printf("Error\nNo map file /to much files were entered.\n"));
	if (check_map_name(argv[1]) == 1)
		return (ft_printf("Error\nMap name is incorrect.\n"));
	vars_init(&main.map, argv[1]);
    checks_inits(&main);
	main.map._map = copy_map(&main.map);
	render_init(&main);
	sprites_init(&main);
	mlx_hook(main.mlx_win, 2, 1L << 0, key_manager, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	mlx_loop_hook(main.mlx_p, game_refresh, &main);
	mlx_loop(main.mlx_p);
	return (0);
}
