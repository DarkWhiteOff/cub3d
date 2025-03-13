#include "../includes/cub3d.h"

int	close_window(t_main *main)
{
	mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	mlx_destroy_image(main->mlx_p, main->spr_p.img);
	mlx_destroy_image(main->mlx_p, main->spr_angle.img);
	mlx_destroy_image(main->mlx_p, main->img);
	mlx_destroy_window(main->mlx_p, main->mlx_win);
	mlx_destroy_display(main->mlx_p);
	free(main->mlx_p);
	free_grids(&main->map);
	exit (ft_printf("Windows was killed.\n"));
}

void	put_to_zero(t_map *map)
{
	map->z = 0;
	map->q = 0;
	map->s = 0;
	map->d = 0;
	map->left = 0;
	map->right = 0;
}

void	actualise_map_data(t_main *main)
{
	int tmp_x = main->map.dirX;

	if (main->map.z == 1 || main->map.q == 1 || main->map.s == 1 || main->map.d == 1 || main->map.left == 1 || main->map.right == 1)
	{
		if (main->map.z == 1)
		{
			main->map.p_pos_x += main->map.dirX * 5;
			main->map.p_pos_y += main->map.dirY * 5;
		}
		else if (main->map.q == 1)
		{
			main->map.p_pos_x += main->map.dirY * 5;
			main->map.p_pos_y -= main->map.dirX * 5;
		}
		else if (main->map.s == 1)
		{
			main->map.p_pos_x -= main->map.dirX * 5;
			main->map.p_pos_y -= main->map.dirY * 5;
		}
		else if (main->map.d == 1)
		{
			main->map.p_pos_x -= main->map.dirY * 5;
			main->map.p_pos_y += main->map.dirX * 5;
		}
		else if (main->map.left == 1)
		{
			main->map.dirX = main->map.dirX * cos(-0.15000) - main->map.dirY * sin(-0.15000);
			main->map.dirY = tmp_x * sin(-0.15000) + main->map.dirY * cos(-0.15000);
			tmp_x = main->map.planeX;
			main->map.planeX = main->map.planeX * cos(-0.15000) - main->map.planeY * sin(-0.15000);
			main->map.planeY = tmp_x * sin(-0.15000) + main->map.planeY * cos(-0.15000);
		}
		else if (main->map.right == 1)
		{
			main->map.dirX = main->map.dirX * cos(0.15000) - main->map.dirY * sin(0.15000);
			main->map.dirY = tmp_x * sin(0.15000) + main->map.dirY * cos(0.15000);
			tmp_x = main->map.planeX;
			main->map.planeX = main->map.planeX * cos(0.15000) - main->map.planeY * sin(0.15000);
			main->map.planeY = tmp_x * sin(0.15000) + main->map.planeY * cos(0.15000);
		}
	}
}

int	key_manager(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == 65307)
		close_window(main);
	if (keycode == 119) // 122
		main->map.z = 1;
	if (keycode == 97) // 113
		main->map.q = 1;
	if (keycode == 115)
		main->map.s = 1;
	if (keycode == 100)
		main->map.d = 1;
	if (keycode == 65361)
		main->map.left = 1;
	if (keycode == 65363)
		main->map.right = 1;
	actualise_map_data(main);
	return (0);
}