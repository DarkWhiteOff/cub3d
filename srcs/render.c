#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_texture(t_main *main, t_img *i, int ray_count, int wall_height)
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)i->height;
	ds = ((float)WIN_H / 2) - (float)wall_height;
	cy[1] = ds;
	z = -1;
	while (++z < i->height)
	{
		color = blue;
		cy[0] = cy[1];
		while (cy[0] < cy[1] + dy)
		{
			if (cy[0] >= 0 && cy[0] < (float)WIN_H)
				my_mlx_pixel_put(&g->win_img, ray_count, cy[0], color);
			cy[0]++;
		}
		cy[1] += dy;
	}
}

void	raycasting(t_main *main)
{
	float distance = 0.0;
	float ray_angle = main->ay.ray_angle - main->ray.HFOV;
	int i = -1;
	int wall_h = 0;

	while (++i < main->map.px_w)
	{
		main->ray.cos = cos(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.sin = sin(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.d_ray_pos.x = main->ray.d_player_pos.x; // + 0.5?
		main->ray.d_ray_pos.y = main->ray.d_player_pos.y;
		while (!ft_strchr("1", main->map.grid[(int)main->ray.d_ray_pos.y][(int)main->ray.d_ray_pos.x]) && \
			sqrt(powf(main->ray.d_ray_pos.x - main->ray.d_player_pos.x - 0.5, 2.) + \
			powf(main->ray.d_ray_pos.y - main->ray.d_player_pos.y - 0.5, 2.)) < main->ray.limit)
		{
			
			main->ray.d_ray_pos.x += main->ray.cos;
			main->ray.d_ray_pos.y += main->ray.sin;
		}
		distance = sqrt(powf(main->ray.d_ray_pos.x - main->ray.d_player_pos.x - 0.5, 2.) + powf(main->ray.d_ray_pos.y - main->ray.d_player_pos.y - 0.5, 2.));
		distance = distance * cos(degree_to_radians(ray_angle - main->ray.ray_angle))
		wall_h = (int)(main->map.px_h / (1.5 * distance));
		float ds = ((float)main->map.px_h / 2) - (float)wall_h;
		int j = -1;
		while (++j < main->map.px_h)
		{
			if (j < ds)
				my_mlx_pixel_put(&main->mlx_win, i, j, green);
			else if (j >= (WIN_H / 2) + wall_height)
				my_mlx_pixel_put(&main->mlx_win, i, j, red);
		}
		//draw_texture(main, get_texture(g), i, wall_h);
		ray_angle += main->ray.diff_ray_angle;
	}
}

int	game_refresh(t_main *main)
{
	int	i;
	int	px_h;
	static int check;

	i = 0;
	px_h = 0;

	actualise_map_data(main); // MOVES
	raycasting(main); // RAYCAST
	while (i < main->map.h)
	{
		update_map(main, i, px_h, check);
		i++;
		px_h += 48;
	}
	return (0);
}

void	update_map(t_main *main, int i, int px_h, int check)
{
	int	j;
	int	px_w;

	j = 0;
	px_w = 0;
	(void)check;
	while (j < main->map.w)
	{
		if (main->map.grid[i][j] == '1')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_wall.img, px_w, px_h);
		if (main->map.grid[i][j] == '0')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_floor.img, px_w, px_h);
		j++;
		px_w += 48;
	}
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_p.img, main->map.p_pos_x, main->map.p_pos_y);
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_angle.img, main->map.p_pos_x + main->map.dirX * 15, main->map.p_pos_y + main->map.dirY * 15);
}
