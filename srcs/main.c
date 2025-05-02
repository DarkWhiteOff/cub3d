/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:08 by zamgar            #+#    #+#             */
/*   Updated: 2025/05/02 16:34:58 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	vars_init(t_main *main, char *map_path)
{
	main->mlx_p = NULL;
	main->mlx_win = NULL;
	main->img = NULL;
	main->addr = NULL;
	main->b = 0;
	main->ls = 0;
	main->end = 0;
	main->p_pos.x = -1;
	main->p_pos.y = -1;
	map_init(&main->map, map_path);
	ray_init(&main->ray);
	tex_init(&main->tex);
	main->ray.diff_ray_angle = 2 * main->ray.HFOV / main->map.px_w;
	main->fd = -1;
	main->fd1 = -1;
	main->fd2 = -1;
	main->fd3 = -1;
}

void	checks_inits(t_main *main)
{
	get_infos(main);
	parse_map(main);
	grid_init(main);
	check_walls1(main);
	check_walls2(main);
	check_epc(main, &main->p_pos);
	main->map.px_player_pos.x = (size_t)main->p_pos.x * 48;
	main->map.px_player_pos.y = (size_t)main->p_pos.y * 48;
	main->map.d_player_pos.x = (float)(main->p_pos.x);
	main->map.d_player_pos.y = (float)(main->p_pos.y);
	main->map.grid[main->p_pos.y][main->p_pos.x] = '0';
	check_path(main, main->p_pos.x, main->p_pos.y);
}

void	ffree(t_main *main)
{
	free(main->map.diff_w);
	free_textures(main);
	free_grids(main);
}

void	render_init(t_main *main)
{
	main->mlx_p = mlx_init();
	if (!main->mlx_p)
	{
		ffree(main);
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->mlx_win = mlx_new_window(main->mlx_p,
			main->map.px_w, main->map.px_h, "cub3d");
	if (!main->mlx_win)
	{
		ffree(main);
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->img = mlx_new_image(main->mlx_p, main->map.px_w, main->map.px_h);
	if (!main->img)
	{
		ffree(main);
		mlx_destroy_window(main->mlx_p, main->mlx_win);
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
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
	main.addr = mlx_get_data_addr(main.img, &main.b, &main.ls, &main.end);
	sprites_init(&main);
	game_refresh(&main);
	mlx_hook(main.mlx_win, 2, 1L << 0, key_manager_down, &main);
	mlx_hook(main.mlx_win, 3, 1L << 1, key_manager_up, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	mlx_loop_hook(main.mlx_p, game_refresh, &main);
	mlx_loop(main.mlx_p);
	return (0);
}
