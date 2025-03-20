#include "../includes/cub3d.h"

void	free_sprites(t_main *main)
{
	if (main->spr_p.img)
		mlx_destroy_image(main->mlx_p, main->spr_p.img);
	if (main->spr_wall.img)
		mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	if (main->spr_floor.img)
		mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	if (main->spr_angle.img)
		mlx_destroy_image(main->mlx_p, main->spr_angle.img);
	mlx_destroy_image(main->mlx_p, main->img);
	mlx_destroy_window(main->mlx_p, main->mlx_win);
	mlx_destroy_display(main->mlx_p);
	free(main->mlx_p);
	free_grids(main);
	free(main->map.diff_w);
	free_textures(main);
}

void	sprites_init(t_main *main)
{
	main->spr_wall.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_wall.xpm", &main->spr_wall.w, &main->spr_wall.h);
	main->spr_floor.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_floor.xpm", &main->spr_floor.w, &main->spr_floor.h);
	main->spr_p.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_player.xpm", &main->spr_p.w, &main->spr_p.h);
	main->spr_angle.img = mlx_xpm_file_to_image(main->mlx_p,
		"spr_tiles/spr_angle.xpm", &main->spr_angle.w, &main->spr_angle.h);
	if (!main->spr_p.img || !main->spr_wall.img
		|| !main->spr_floor.img || !main->spr_angle.img)
	{
		free_sprites(main);
		exit(ft_printf("Error\nSprites init FAILED"));
	}
}
