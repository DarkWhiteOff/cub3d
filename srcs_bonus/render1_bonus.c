/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:13 by zamgar            #+#    #+#             */
/*   Updated: 2025/05/01 14:04:41 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	find_tex(t_main *main, t_img_i *tex, float ray_sin, float ray_cos)
{
	if (main->map.grid[(int)(main->ray.d_ray_pos.y - ray_sin)]
		[(int)main->ray.d_ray_pos.x] != '1')
		*tex = main->tex.tex_north;
	else if (main->map.grid[(int)(main->ray.d_ray_pos.y + ray_sin)]
		[(int)main->ray.d_ray_pos.x] != '1')
		*tex = main->tex.tex_south;
	else if (main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)(main->ray.d_ray_pos.x + ray_cos)] != '1')
		*tex = main->tex.tex_east;
	else if (main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)(main->ray.d_ray_pos.x - ray_cos)] != '1')
		*tex = main->tex.tex_west;
}

unsigned int	my_mlx_pixel_get2(t_main *main, int x, int y)
{
	float	ray_cos;
	float	ray_sin;
	char	*dst;
	t_img_i	tex;

	ray_cos = main->ray.cos;
	if (ray_cos < 0)
		ray_cos = -ray_cos;
	ray_sin = main->ray.sin;
	if (ray_sin < 0)
		ray_sin = -ray_sin;
	tex = main->tex.tex_south;
	if (main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)main->ray.d_ray_pos.x] == 'D')
	{
		tex = main->tex.tex_door;
		dst = tex.addr + (y * tex.ls + x * (tex.b / 8));
		return (*(unsigned int *)dst);
	}
	find_tex(main, &tex, ray_sin, ray_cos);
	dst = tex.addr + (y * tex.ls + x * (tex.b / 8));
	return (*(unsigned int *)dst);
}

void	ray_pos_calc(t_main *main, int ray_angle)
{
	main->ray.d_ray_pos.x = main->map.d_player_pos.x + 0.5;
	main->ray.d_ray_pos.y = main->map.d_player_pos.y + 0.5;
	while (!ft_strchr("1", main->map.grid[(int)main->ray.d_ray_pos.y]
			[(int)main->ray.d_ray_pos.x])
		&& !ft_strchr("D", main->map.grid[(int)main->ray.d_ray_pos.y]
			[(int)main->ray.d_ray_pos.x]))
	{	
		main->ray.d_ray_pos.x += main->ray.cos;
		main->ray.d_ray_pos.y += main->ray.sin;
	}
}

int	wall_height_calc(t_main *main, int ray_angle)
{
	float	distance;
	int		wall_h;

	distance = 0.0;
	wall_h = 0;
	distance = sqrt(powf(main->ray.d_ray_pos.x
				- main->map.d_player_pos.x - 0.5, 2.0)
			+ powf(main->ray.d_ray_pos.y
				- main->map.d_player_pos.y - 0.5, 2.0));
	distance = distance * cos(degree_to_radians(ray_angle
				- main->ray.ray_angle));
	wall_h = (int)(main->map.px_h / (1.5 * distance));
	return (wall_h);
}

int	get_tex_color(t_main *main, int z)
{
	int	color;

	color = 0x00000000;
	if (main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)main->ray.d_ray_pos.x] == '1'
		|| main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)main->ray.d_ray_pos.x] == 'D')
		color = my_mlx_pixel_get2(main, (int)
				(64 * (main->ray.d_ray_pos.x + main->ray.d_ray_pos.y)) % 64, z);
	return (color);
}
