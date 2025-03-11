#include "../includes/cub3d.h"

int	game_refresh(t_main *main)
{
	int	i;
	int	px_h;

	i = 0;
	px_h = 0;
	while (i < main->map.h)
	{
		update_map(main, i, px_h);
		i++;
		px_h += 48;
	}
	return (0);
}

void	update_map(t_main *main, int i, int px_h)
{
	int	j;
	int	px_w;

	j = 0;
	px_w = 0;
	if (main->map.z == 1 || main->map.q == 1 || main->map.s == 1 || main->map.d == 1)
	{
		if (main->map.z == 1)
			main->map.pixel_pos_y = main->map.pixel_pos_y - 10;
		else if (main->map.q == 1)
			main->map.pixel_pos_x = main->map.pixel_pos_x - 10;
		else if (main->map.s == 1)
			main->map.pixel_pos_y = main->map.pixel_pos_y + 10;
		else if (main->map.d == 1)
			main->map.pixel_pos_x = main->map.pixel_pos_x + 10;
		put_to_zero(&main->map);
	}
	while (main->map.grid[i][j] != '\0')
	{
		if (main->map.grid[i][j] == '1')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_wall.img, px_w, px_h);
		if (main->map.grid[i][j] == '0')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_floor.img, px_w, px_h);
				mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_p.img, main->map.pixel_pos_x, main->map.pixel_pos_y);
		j++;
		px_w += 48;
	}
}