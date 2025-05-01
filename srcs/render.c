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

#include "../includes/cub3d.h"

int	get_tex_color(t_main *main, int z)
{
	int	color;

	color = 0x00000000;
	if (main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)main->ray.d_ray_pos.x] == '1')
		color = my_mlx_pixel_get2(main, (int)
				(64 * (main->ray.d_ray_pos.x + main->ray.d_ray_pos.y)) % 64, z);
	return (color);
}

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

int	game_refresh(t_main *main)
{
	actualise_player(main);
	raycasting(main);
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->img, 0, 0);
	return (0);
}
