/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:05 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/19 11:29:57 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_init(t_map *map, char *map_path)
{
	map->path = map_path;
	map->h = 0;
	map->w = 0;
	map->px_h = 480;
	map->px_w = 640;
	map->diff_w = NULL;
	map->w_max = 0;
	map->player_pos = 0;
	map->fd = -1;
	map->grid = NULL;
	map->z = 0;
	map->q = 0;
	map->s = 0;
	map->d = 0;
	map->left = 0;
	map->right = 0;
	map->px_player_pos.x = 0;
	map->px_player_pos.y = 0;
	map->d_player_pos.x = 0.0;
	map->d_player_pos.y = 0.0;
}

void	ray_init(t_ray *ray, t_map *map)
{
	ray->fov = 60.0;
	ray->hfov = 30.0;
	ray->ray_angle = 0.0;
	ray->diff_ray_angle = 2 * ray->hfov / map->px_w;
	ray->precision = 50.0;
	ray->limit = 11.0;
	ray->cos = 0.0;
	ray->sin = 0.0;
	ray->d_ray_pos.x = 0.0;
	ray->d_ray_pos.y = 0.0;
}

void	tex_init(t_tex *tex)
{
	tex->no = NULL;
	tex->so = NULL;
	tex->we = NULL;
	tex->ea = NULL;
	tex->color_f = -1;
	tex->color_c = -1;
	tex->map_start = 0;
	tex->tex_north.addr = NULL;
	tex->tex_north.b = 0;
	tex->tex_north.ls = 0;
	tex->tex_north.end = 0;
}

void	textures_init(t_main *main)
{
	main->tex.tex_north.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.no, &main->tex.tex_north.w, &main->tex.tex_north.h);
	main->tex.tex_south.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.so, &main->tex.tex_south.w, &main->tex.tex_south.h);
	main->tex.tex_west.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.we, &main->tex.tex_west.w, &main->tex.tex_west.h);
	main->tex.tex_east.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.ea, &main->tex.tex_east.w, &main->tex.tex_east.h);
}

void	sprites_init(t_main *main)
{
	main->spr_wall.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_wall.xpm", &main->spr_wall.w, &main->spr_wall.h);
	main->spr_floor.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_floor.xpm", &main->spr_floor.w, &main->spr_floor.h);
	main->spr_p.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_player.xpm", &main->spr_p.w, &main->spr_p.h);
	textures_init(main);
	if (!main->spr_p.img || !main->spr_wall.img
		|| !main->spr_floor.img || !main->tex.tex_north.img
		|| !main->tex.tex_south.img || !main->tex.tex_west.img
		|| !main->tex.tex_east.img)
	{
		free_sprites(main);
		exit(ft_printf("Error\nSprites/Textures init FAILED"));
	}
	get_img_addr(main);
}
