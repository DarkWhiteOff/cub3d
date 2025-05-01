/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:13 by zamgar            #+#    #+#             */
/*   Updated: 2025/04/08 18:39:13 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_texture(t_main *main, int ray_count, int wall_height)
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)main->tex.tex_north.w;
	ds = ((float)main->map.px_h / 2) - (float)wall_height;
	cy[1] = ds;
	z = -1;
	while (++z < main->tex.tex_north.w)
	{
		color = get_tex_color(main, z);
		cy[0] = cy[1];
		while (cy[0] < cy[1] + dy)
		{
			if (cy[0] >= 0 && cy[0] < (float)main->map.px_h)
				my_mlx_pixel_put(main->addr, main->ls, main->b,
					ray_count, cy[0], color);
			cy[0]++;
		}
		cy[1] += dy;
	}
}

void	draw_ceiling_floor(t_main *main, int i, int wall_h, int ds)
{
	int		j;

	j = -1;
	while (++j < main->map.px_h)
	{
		if (j < ds)
			my_mlx_pixel_put(main->addr, main->ls, main->b,
				i, j, main->tex.color_c);
		else if (j >= (main->map.px_h / 2) + wall_h)
			my_mlx_pixel_put(main->addr, main->ls, main->b,
				i, j, main->tex.color_f);
	}
}

void	raycasting(t_main *main)
{
	int		i;
	float	ray_angle;
	int		wall_h;
	float	ds;

	i = -1;
	ray_angle = main->ray.ray_angle - main->ray.HFOV;
	wall_h = 0;
	ds = 0.0;
	while (++i < main->map.px_w)
	{
		main->ray.cos = cos(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.sin = sin(degree_to_radians(ray_angle)) / main->ray.precision;
		ray_pos_calc(main, ray_angle);
		wall_h = wall_height_calc(main, ray_angle);
		ds = ((float)main->map.px_h / 2) - (float)wall_h;
		draw_ceiling_floor(main, i, wall_h, ds);
		draw_texture(main, i, wall_h);
		ray_angle += main->ray.diff_ray_angle;
	}
}

void	update_map(t_main *main, int i, int px_h)
{
	int	j;
	int	px_w;

	j = 0;
	px_w = 0;
	while (main->map.grid[i][j] != '\0')
	{
		if (main->map.grid[i][j] == '1')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_wall.img, px_w, px_h);
		if (main->map.grid[i][j] == '0')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_floor.img, px_w, px_h);
		j++;
		px_w += 5;
	}
	mlx_put_image_to_window(main->mlx_p, main->mlx_win,
		main->spr_p.img, main->map.d_player_pos.x * 5,
		main->map.d_player_pos.y * 5);
}

int	game_refresh(t_main *main)
{
	int	i;
	int	px_h;

	i = 0;
	px_h = 0;
	actualise_player(main);
	raycasting(main);
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->img, 0, 0);
	while (i < main->map.h)
	{
		update_map(main, i, px_h);
		i++;
		px_h += 5;
	}
	return (0);
}
