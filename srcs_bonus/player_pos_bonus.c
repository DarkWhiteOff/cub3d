/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:11 by zamgar            #+#    #+#             */
/*   Updated: 2025/04/08 18:39:11 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	close_window(t_main *main)
{
	mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	mlx_destroy_image(main->mlx_p, main->spr_p.img);
	mlx_destroy_image(main->mlx_p, main->tex.tex_north.img);
	mlx_destroy_image(main->mlx_p, main->tex.tex_south.img);
	mlx_destroy_image(main->mlx_p, main->tex.tex_west.img);
	mlx_destroy_image(main->mlx_p, main->tex.tex_east.img);
	mlx_destroy_image(main->mlx_p, main->tex.tex_door.img);
	mlx_destroy_image(main->mlx_p, main->img_minimap);
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
	float	x;
	float	y;
	float	ray_cos;
	float	ray_sin;

	x = main->map.d_player_pos.x;
	y = main->map.d_player_pos.y;
	ray_cos = cos(degree_to_radians(angle)) * 0.02;
	ray_sin = sin(degree_to_radians(angle)) * 0.02;
	if (!ft_strchr("1", main->map.grid[(int)(y + 0.5 + (3 * ray_sin))]
		[(int)(x + 0.5)]))
		main->map.d_player_pos.y += ray_sin;
	if (!ft_strchr("1", main->map.grid[(int)(y + 0.5)]
		[(int)(x + 0.5 + (3 * ray_cos))]))
		main->map.d_player_pos.x += ray_cos;
	main->p_pos.x = (int)main->map.d_player_pos.x;
	main->p_pos.y = (int)main->map.d_player_pos.y;
}

void	rotation_left(t_main *main)
{
	if (main->map.left == 1 || main->m_left == 1)
	{
		if (main->map.left == 1)
		{
			if (main->ray.ray_angle <= 0)
				main->ray.ray_angle = 360;
			else
				main->ray.ray_angle -= 0.5;
		}
		else if (main->m_left == 1)
		{
			if (main->ray.ray_angle <= 0)
				main->ray.ray_angle = 360;
			else
				main->ray.ray_angle -= 3;
		}
	}
}

void	rotation_right(t_main *main)
{
	if (main->map.right == 1 || main->m_right == 1)
	{
		if (main->map.right == 1)
		{
			if (main->ray.ray_angle >= 360)
				main->ray.ray_angle = 0;
			else
				main->ray.ray_angle += 0.5;
		}
		else if (main->m_right == 1)
		{
			if (main->ray.ray_angle >= 360)
				main->ray.ray_angle = 0;
			else
				main->ray.ray_angle += 3;
		}
	}
}

void	actualise_player(t_main *main)
{
	float	angle;

	angle = main->ray.ray_angle;
	if (main->map.z == 1)
		move(angle, main);
	if (main->map.q == 1)
	{
		angle = main->ray.ray_angle - 90;
		move(angle, main);
	}
	if (main->map.s == 1)
	{
		angle = main->ray.ray_angle - 180;
		move(angle, main);
	}
	if (main->map.d == 1)
	{
		angle = main->ray.ray_angle + 90;
		move(angle, main);
	}
	rotation_left(main);
	rotation_right(main);
	main->m_left = 0;
	main->m_right = 0;
}
