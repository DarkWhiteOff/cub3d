#include "../includes/cub3d_bonus.h"

void	map_init(t_map *map, char *map_path)
{
	//Checks
	map->path = map_path;
	map->h = 0;
	map->w = 0;
	map->px_h = 480;
	map->px_w = 640;
	map->diff_w = NULL;
	map->player_pos = 0;
	map->fd = -1;
	map->grid = NULL;
	map->highlight_grid = NULL;
	//Controls
	map->z = 0;
	map->q = 0;
	map->s = 0;
	map->d = 0;
	map->left = 0;
	map->right = 0;
	//Math
	map->px_player_pos.x = 0;
	map->px_player_pos.y = 0;
	map->d_player_pos.x = 0.0;
	map->d_player_pos.y = 0.0;
}

void	ray_init(t_ray *ray)
{
	ray->FOV = 60.0;
	ray->HFOV = 30.0;
	ray->ray_angle = 0.0;
	ray->diff_ray_angle = 0.0;
	ray->precision = 50.0;
	ray->limit = 11.0;
	ray->cos = 0.0;
	ray->sin = 0.0;
	ray->d_ray_pos.x = 0.0;
	ray->d_ray_pos.y = 0.0;
}

void	tex_init(t_tex *tex)
{
	tex->NO = NULL;
	tex->SO = NULL;
	tex->WE = NULL;
	tex->EA = NULL;
	tex->D = NULL;
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
			main->tex.NO, &main->tex.tex_north.w, &main->tex.tex_north.h);
	main->tex.tex_south.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.SO, &main->tex.tex_south.w, &main->tex.tex_south.h);
	main->tex.tex_west.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.WE, &main->tex.tex_west.w, &main->tex.tex_west.h);
	main->tex.tex_east.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.EA, &main->tex.tex_east.w, &main->tex.tex_east.h);
	if (main->tex.D)
	{
		printf("door path = '%s'\n", main->tex.D);
		main->tex.tex_door.img = mlx_xpm_file_to_image(main->mlx_p,
			main->tex.D, &main->tex.tex_door.w, &main->tex.tex_door.h);

	}
}

void	sprites_init(t_main *main)
{
	// Sprites
	main->spr_wall.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_wall.xpm", &main->spr_wall.w, &main->spr_wall.h);
	main->spr_floor.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_floor.xpm", &main->spr_floor.w, &main->spr_floor.h);
	main->spr_p.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_player.xpm", &main->spr_p.w, &main->spr_p.h);
	main->spr_angle.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_angle.xpm", &main->spr_angle.w, &main->spr_angle.h);
	// Textures
	textures_init(main);
	if (!main->spr_p.img || !main->spr_wall.img
		|| !main->spr_floor.img || !main->spr_angle.img
		|| !main->tex.tex_north.img || !main->tex.tex_south.img
		|| !main->tex.tex_west.img || !main->tex.tex_east.img)
	{
		free_sprites(main);
		exit(ft_printf("Error\nSprites/Textures init FAILED"));
	}
	main->tex.tex_north.addr = mlx_get_data_addr(main->tex.tex_north.img, &main->tex.tex_north.b, &main->tex.tex_north.ls, &main->tex.tex_north.end);
	main->tex.tex_south.addr = mlx_get_data_addr(main->tex.tex_south.img, &main->tex.tex_south.b, &main->tex.tex_south.ls, &main->tex.tex_south.end);
	main->tex.tex_west.addr = mlx_get_data_addr(main->tex.tex_west.img, &main->tex.tex_west.b, &main->tex.tex_west.ls, &main->tex.tex_west.end);
	main->tex.tex_east.addr = mlx_get_data_addr(main->tex.tex_east.img, &main->tex.tex_east.b, &main->tex.tex_east.ls, &main->tex.tex_east.end);
	if (main->tex.D && main->tex.tex_door.img)
		main->tex.tex_door.addr = mlx_get_data_addr(main->tex.tex_door.img, &main->tex.tex_door.b, &main->tex.tex_door.ls, &main->tex.tex_door.end);
}
