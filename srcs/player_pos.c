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

float	degree_to_radians(float degree)
{
	return (degree * PI / 180);
}

void	move(float angle, t_main *main)
{
	float x = main->map.d_player_pos.x;
	float y = main->map.d_player_pos.y;
	float ray_cos;
	float ray_sin;

	ray_cos = cos(degree_to_radians(angle)) * 0.05;
	ray_sin = sin(degree_to_radians(angle)) * 0.05;
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
		main->ray.ray_angle -= 0.6;
	else if (main->map.right == 1)
		main->ray.ray_angle += 0.6;
}

int	key_manager_down(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == KEY_ESC)
		close_window(main);
	if (keycode == KEY_W)
		main->map.z = 1;
	if (keycode == KEY_A)
		main->map.q = 1;
	if (keycode == KEY_S)
		main->map.s = 1;
	if (keycode == KEY_D)
		main->map.d = 1;
	if (keycode == KEY_LEFT)
		main->map.left = 1;
	if (keycode == KEY_RIGHT)
		main->map.right = 1;
	return (0);
}

int	key_manager_up(int keycode, t_main *main)
{
	if (keycode == KEY_W)
		main->map.z = 0;
	if (keycode == KEY_A)
		main->map.q = 0;
	if (keycode == KEY_S)
		main->map.s = 0;
	if (keycode == KEY_D)
		main->map.d = 0;
	if (keycode == KEY_LEFT)
		main->map.left = 0;
	if (keycode == KEY_RIGHT)
		main->map.right = 0;
	return (0);
}