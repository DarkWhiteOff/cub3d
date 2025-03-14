#include "../includes/cub3d.h"

void map_init (t_map *map, char *map_path)
{
	//Checks
	map->path = map_path;
	map->h = 0;
	map->w = 0;
	map->px_h = 0;
	map->px_w = 0;
	map->player_pos = 0;
	map->grid = NULL;
	map->highlight_grid = NULL;
	map->sc_s.x = 0;
	map->sc_s.y = 0;
	//Controls
	map->z = 0;
	map->q = 0;
	map->s = 0;
	map->d = 0;
	map->left = 0;
	map->right = 0;
	//Math
	map->px_player_pos.x = 0;
	map->px_player_pos.y = 0;
	map->d_player_pos.x = 0.0;
	map->d_player_pos.y = 0.0;
}

void ray_init (t_ray *ray)
{
	ray->FOV = 60.0;
	ray->HFOV = 30.0;
	ray->ray_angle = 270.0; // N (270º), S (90º), W (180º), E (0º) 
	ray->diff_ray_angle = 0.0;
	ray->precision = 50.0;
	ray->limit = 11.0;
	ray->cos = 0.0;
	ray->sin = 0.0;
	ray->d_player_pos.x = 0.0;
	ray->d_player_pos.y = 0.0;
	ray->d_ray_pos.x = 0.0;
	ray->d_ray_pos.y = 0.0;
}

void	vars_init(t_main *main, char *map_path)
{
	map_init(&main->map, map_path);
	ray_init(&main->ray);
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
	main->map.px_h = main->map.h * 48;
	main->map.px_w = main->map.w * 48;
	main->ray.diff_ray_angle = 2 * HFOV / main->map.px_w;
	grid_init(main);
	check_walls1(&main->map);
	check_walls2(&main->map);
	check_epc(&main->map, &main->p_pos);
	main->map.px_player_pos.x = (size_t)main->p_pos.x * 48;
	main->map.px_player_pos.y = (size_t)main->p_pos.y * 48;
	main->ray.d_player_pos.x = (int)(main->p_pos.x + 0.5);
	main->ray.d_player_pos.y = (int)(main->p_pos.y + 0.5);
	ray->d_ray_pos.x = main->ray.d_player_pos.x;
	ray->d_ray_pos.y = main->ray.d_player_pos.y;
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
	vars_init(&main, argv[1]);
    checks_inits(&main);
	render_init(&main);
	sprites_init(&main);
	game_refresh(&main);
	mlx_hook(main.mlx_win, 2, 1L << 0, key_manager, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	mlx_loop_hook(main.mlx_p, game_refresh, &main);
	mlx_loop(main.mlx_p);
	return (0);
}
