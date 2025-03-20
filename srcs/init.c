#include "../includes/cub3d.h"

void map_init (t_map *map, char *map_path)
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

void ray_init (t_ray *ray)
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

void tex_init (t_tex *tex)
{
	tex->NO = NULL;
	tex->SO = NULL;
	tex->WE = NULL;
	tex->EA = NULL;
	tex->color_f = -1;
	tex->color_c = -1;
	tex->map_start = 0;
}
