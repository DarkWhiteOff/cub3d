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
	map->r = 0;
	map->mx = 0;
	map->mp = 0;
	map->dof = 0;
	map->rx = 0;
	map->ry = 0;
	map->ra = 0;
	map->xo = 0;
	map->yo = 0;
}

int	key_manager(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == 65307)
		close_window(main);
	if (keycode == 119) // 122
		main->map.z = 1;
	if (keycode == 97) // 113w
		main->map.q = 1;
	if (keycode == 115)
		main->map.s = 1;
	if (keycode == 100)
		main->map.d = 1;
	// if (keycode == 65362) // up
	if (keycode == 65361) // left
		main->map.left = 1;
	if (keycode == 65363) // right
		main->map.right = 1;
	// if (keycode == 65364) // down
	return (0);
}