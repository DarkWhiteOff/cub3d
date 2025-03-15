#include "../includes/cub3d.h"

void	my_mlx_pixel_put(void *img, char *adrr, int ls, int b, int x, int y, int color)
{
	char	*dst;

	(void)img;
	dst = adrr + (y * ls + x * (b / 8));
	*(unsigned int *)dst = color;
}

void	draw_texture(t_main *main, int ray_count, int wall_height)
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)90;
	ds = ((float)main->map.px_h / 2) - (float)wall_height;
	cy[1] = ds;
	z = -1;
	while (++z < 90)
	{
		color = blue;
		cy[0] = cy[1];
		while (cy[0] < cy[1] + dy)
		{
			if (cy[0] >= 0 && cy[0] < (float)main->map.px_h)
				my_mlx_pixel_put(&main->img, main->addr, main->ls, main->b, ray_count, cy[0], color);
			cy[0]++;
		}
		cy[1] += dy;
	}
}

void	raycasting(t_main *main)
{
	float distance = 0.0;
	float ray_angle = main->ray.ray_angle - main->ray.HFOV;
	int i = -1;
	int wall_h = 0;
	float ds = 0.0;
	int j = -1;

	while (++i < main->map.px_w)
	{
		main->ray.cos = cos(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.sin = sin(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.d_ray_pos.x = main->map.d_player_pos.x + 0.5;
		main->ray.d_ray_pos.y = main->map.d_player_pos.y + 0.5;
		while (!ft_strchr("1", main->map.grid[(int)main->ray.d_ray_pos.y][(int)main->ray.d_ray_pos.x]) && \
			sqrt(powf(main->ray.d_ray_pos.x - main->map.d_player_pos.x - 0.5, 2.) + \
			powf(main->ray.d_ray_pos.y - main->map.d_player_pos.y - 0.5, 2.)) < main->ray.limit)
		{
			
			main->ray.d_ray_pos.x += main->ray.cos;
			main->ray.d_ray_pos.y += main->ray.sin;
		}
		distance = sqrt(powf(main->ray.d_ray_pos.x - main->map.d_player_pos.x - 0.5, 2.) + powf(main->ray.d_ray_pos.y - main->map.d_player_pos.y - 0.5, 2.));
		distance = distance * cos(degree_to_radians(ray_angle - main->ray.ray_angle));
		
		wall_h = (int)(main->map.px_h / (1.5 * distance));
		ds = ((float)main->map.px_h / 2) - (float)wall_h;
		j = -1;
		while (++j < main->map.px_h)
		{
			if (j < ds)
				my_mlx_pixel_put(&main->img, main->addr, main->ls, main->b, i, j, green);
			else if (j >= (main->map.px_h / 2) + wall_h)
				my_mlx_pixel_put(&main->img, main->addr, main->ls, main->b, i, j, red);
		}
		draw_texture(main, i, wall_h);
		ray_angle += main->ray.diff_ray_angle;
	}
}

int	game_refresh(t_main *main)
{
	if (!(main->nframes % main->rate))
	{
		actualise_map_data(main); // MOVES
		raycasting(main); // RAYCAST
		mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->img, 0, 0);
	}
	main->nframes++;
	return (0);
}
