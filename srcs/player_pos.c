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
	free_grids(main);
	free(main->map.diff_w);
	free_textures(main);
	exit (ft_printf("Windows was killed.\n"));
}

void	move(float angle, t_main *main)
{
	float x = main->map.d_player_pos.x;
	float y = main->map.d_player_pos.y;
	float ray_cos;
	float ray_sin;

	ray_cos = cos(degree_to_radians(angle)) * 0.06;
	ray_sin = sin(degree_to_radians(angle)) * 0.06;
	if (!ft_strchr("1", main->map.grid[(int)(y + 0.5 + (3 * ray_sin))][(int)(x + 0.5)]))
		main->map.d_player_pos.y += ray_sin;
	if (!ft_strchr("1", main->map.grid[(int)(y + 0.5)][(int)(x + 0.5 + (3 * ray_cos))]))
		main->map.d_player_pos.x += ray_cos;
}

void	actualise_player(t_main *main)
{
	float angle;

	angle = main->ray.ray_angle;
	if (main->map.z == 1)
		move(angle, main);
	else if (main->map.q == 1)
	{
		angle = main->ray.ray_angle - 90;
		move(angle, main);
	}
	else if (main->map.s == 1)
	{
		angle = main->ray.ray_angle - 180;
		move(angle, main);
	}
	else if (main->map.d == 1)
	{
		angle = main->ray.ray_angle + 90;
		move(angle, main);
	}
	else if (main->map.left == 1)
		main->ray.ray_angle -= 1;
	else if (main->map.right == 1)
		main->ray.ray_angle += 1;
}

int	key_manager_down(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == 65307)
		close_window(main);
	if (keycode == 119) // 119
		main->map.z = 1;
	if (keycode == 97) // 97
		main->map.q = 1;
	if (keycode == 115)
		main->map.s = 1;
	if (keycode == 100)
		main->map.d = 1;
	if (keycode == 65361)
		main->map.left = 1;
	if (keycode == 65363)
		main->map.right = 1;
	return (0);
}

int	key_manager_up(int keycode, t_main *main)
{
	if (keycode == 119) // 119
		main->map.z = 0;
	if (keycode == 97) // 97
		main->map.q = 0;
	if (keycode == 115)
		main->map.s = 0;
	if (keycode == 100)
		main->map.d = 0;
	if (keycode == 65361)
		main->map.left = 0;
	if (keycode == 65363)
		main->map.right = 0;
	return (0);
}
