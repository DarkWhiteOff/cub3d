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

void	my_mlx_pixel_put(char *adrr, int ls, int b, int x, int y, int color)
{
	char	*dst;

	dst = adrr + (y * ls + x * (b / 8));
	*(unsigned int *)dst = color;
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
	if (main->map.grid[(int)main->ray.d_ray_pos.y][(int)main->ray.d_ray_pos.x] == 'D')
	{
		tex = main->tex.tex_door;
		dst = tex.addr + (y * tex.ls + x * (tex.b / 8));
		return (*(unsigned int *)dst);
	}
	if (main->map.grid[(int)(main->ray.d_ray_pos.y - ray_sin)]
		[(int)main->ray.d_ray_pos.x] != '1')
		tex = main->tex.tex_north;
	else if (main->map.grid[(int)(main->ray.d_ray_pos.y + ray_sin)]
		[(int)main->ray.d_ray_pos.x] != '1')
		tex = main->tex.tex_south;
	else if (main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)(main->ray.d_ray_pos.x + ray_cos)] != '1')
		tex = main->tex.tex_east;
	else if (main->map.grid[(int)main->ray.d_ray_pos.y]
		[(int)(main->ray.d_ray_pos.x - ray_cos)] != '1')
		tex = main->tex.tex_west;
	dst = tex.addr + (y * tex.ls + x * (tex.b / 8));
	return (*(unsigned int *)dst);
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
	float	distance;
	float	ray_angle;
	int		i;
	int		wall_h;
	float	ds;
	int		j;

	distance = 0.0;
	ray_angle = main->ray.ray_angle - main->ray.HFOV;
	i = -1;
	wall_h = 0;
	ds = 0.0;
	j = -1;
	while (++i < main->map.px_w)
	{
		//Ray end pos calculations
		main->ray.cos = cos(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.sin = sin(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.d_ray_pos.x = main->map.d_player_pos.x + 0.5;
		main->ray.d_ray_pos.y = main->map.d_player_pos.y + 0.5;
		while (!ft_strchr("1", main->map.grid[(int)main->ray.d_ray_pos.y]
				[(int)main->ray.d_ray_pos.x]) && !ft_strchr("D", main->map.grid[(int)main->ray.d_ray_pos.y]
				[(int)main->ray.d_ray_pos.x]))
		{	
			main->ray.d_ray_pos.x += main->ray.cos;
			main->ray.d_ray_pos.y += main->ray.sin;
		}
		//Wall height calculations
		distance = sqrt(powf(main->ray.d_ray_pos.x - main->map.d_player_pos.x - 0.5, 2.0) + powf(main->ray.d_ray_pos.y - main->map.d_player_pos.y - 0.5, 2.0));
		distance = distance * cos(degree_to_radians(ray_angle - main->ray.ray_angle));
		wall_h = (int)(main->map.px_h / (1.5 * distance));
		ds = ((float)main->map.px_h / 2) - (float)wall_h; //drawStart
		//Put pixels on img (not window)
		j = -1;
		while (++j < main->map.px_h)
		{
			if (j < ds)
				my_mlx_pixel_put(main->addr, main->ls, main->b, i, j, main->tex.color_c); //Ceiling
			else if (j >= (main->map.px_h / 2) + wall_h)
				my_mlx_pixel_put(main->addr, main->ls, main->b, i, j, main->tex.color_f); //Floor
		}
		draw_texture(main, i, wall_h); // Wall
		ray_angle += main->ray.diff_ray_angle;
	}
}

int	game_refresh(t_main *main)
{
	actualise_player(main); // MOVES
	raycasting(main); // RAYCAST
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->img, 0, 0); // REFRESH IMG
	int i = 0;
	int px_h = 0;
	while (i < main->map.h)
	{
		update_map(main, i, px_h);
		i++;
		px_h += 5;
	}
	return (0);
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
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_p.img, main->map.d_player_pos.x * 5, main->map.d_player_pos.y * 5);
}
