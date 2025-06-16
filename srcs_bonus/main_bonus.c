/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zz <zz@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:08 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/16 22:59:43 by zz               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	vars_init(t_main *main, char *map_path)
{
	main->mlx_p = NULL;
	main->mlx_win = NULL;
	main->img = NULL;
	main->img_minimap = NULL;
	main->img_data.addr = NULL;
	main->img_data.b = 0;
	main->img_data.ls = 0;
	main->img_data.end = 0;
	main->p_pos.x = -1;
	main->p_pos.y = -1;
	map_init(&main->map, map_path);
	ray_init(&main->ray);
	tex_init(&main->tex);
	main->ray.diff_ray_angle = 2 * main->ray.hfov / main->map.px_w;
	main->fd = -1;
	main->fd1 = -1;
	main->fd2 = -1;
	main->fd3 = -1;
	main->prev_x = 0;
	main->prev_y = 0;
	main->x = 0;
	main->y = 0;
	main->m_left = 0;
	main->m_right = 0;
}

void	checks_inits(t_main *main)
{
	get_infos(main);
	parse_map(main);
	grid_init(main);
	check_walls1(main);
	check_walls2(main);
	check_horizontal(main);
	check_vertical(main);
	check_epc(main, &main->p_pos);
	main->map.px_player_pos.x = (size_t)main->p_pos.x * 48;
	main->map.px_player_pos.y = (size_t)main->p_pos.y * 48;
	main->map.d_player_pos.x = (float)(main->p_pos.x);
	main->map.d_player_pos.y = (float)(main->p_pos.y);
	main->map.grid[main->p_pos.y][main->p_pos.x] = '0';
}

void	init_minimap(t_main *main)
{
	main->img_minimap = mlx_new_image(main->mlx_p,
			main->map.w * 5, main->map.h * 5);
	if (!main->img)
	{
		free_diff_tex_grids(main);
		mlx_destroy_image(main->mlx_p, main->img);
		mlx_destroy_window(main->mlx_p, main->mlx_win);
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->img_data.addr = mlx_get_data_addr(main->img, &main->img_data.b,
			&main->img_data.ls, &main->img_data.end);
	main->minimap_data.addr = mlx_get_data_addr(main->img_minimap,
			&main->minimap_data.b, &main->minimap_data.ls,
			&main->minimap_data.end);
}

void	render_init(t_main *main)
{
	main->mlx_p = mlx_init();
	if (!main->mlx_p)
	{
		free_diff_tex_grids(main);
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->mlx_win = mlx_new_window(main->mlx_p, main->map.px_w,
			main->map.px_h, "cub3d");
	if (!main->mlx_win)
	{
		free_diff_tex_grids(main);
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->img = mlx_new_image(main->mlx_p, main->map.px_w, main->map.px_h);
	if (!main->img)
	{
		free_diff_tex_grids(main);
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
	init_minimap(&main);
	sprites_init(&main);
	game_refresh(&main);
	mlx_hook(main.mlx_win, 2, 1L << 0, key_manager_down, &main);
	mlx_hook(main.mlx_win, 3, 1L << 1, key_manager_up, &main);
	mlx_hook(main.mlx_win, 6, 1L << 6, mouse_manager, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	mlx_loop_hook(main.mlx_p, game_refresh, &main);
	mlx_loop(main.mlx_p);
	return (0);
}
