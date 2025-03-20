#include "../includes/cub3d.h"

void	free_grids(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->map.h)
	{
		free(main->map.grid[i]);
		free(main->map.highlight_grid[i]);
		i++;
	}
	free(main->map.grid);
	free(main->map.highlight_grid);
}

void free_textures(t_main *main)
{
	if (main->tex.NO)
		free(main->tex.NO);
	if (main->tex.SO)
		free(main->tex.SO);
	if (main->tex.WE)
		free(main->tex.WE);
	if (main->tex.EA)
		free(main->tex.EA);
}

void	free_sprites(t_main *main)
{
	// Sprites
	if (main->spr_p.img)
		mlx_destroy_image(main->mlx_p, main->spr_p.img);
	if (main->spr_wall.img)
		mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	if (main->spr_floor.img)
		mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	if (main->spr_angle.img)
		mlx_destroy_image(main->mlx_p, main->spr_angle.img);
	// Textures
	if (main->tex.tex_north.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_north.img);
	if (main->tex.tex_south.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_south.img);
	if (main->tex.tex_west.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_west.img);
	if (main->tex.tex_east.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_east.img);
	mlx_destroy_image(main->mlx_p, main->img);
	mlx_destroy_window(main->mlx_p, main->mlx_win);
	mlx_destroy_display(main->mlx_p);
	free(main->mlx_p);
	free_grids(main);
	free(main->map.diff_w);
	free_textures(main);
}
