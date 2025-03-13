#include "../includes/cub3d.h"

int	game_refresh(t_main *main)
{
	int	i;
	int	px_h;

	i = 0;
	px_h = 0;
	if (main->map.z == 1 || main->map.q == 1 || main->map.s == 1 || main->map.d == 1 || main->map.left == 1 || main->map.right == 1)
	{
		while (i < main->map.h)
		{
			update_map(main, i, px_h);
			i++;
			px_h += 48;
		}
	}
	return (0);
}

// void drawLine(t_main *main, double beginX, double beginY, double endX, double endY, int color)
// {
//     double deltaX = endX - beginX;
//     double deltaY = endY - beginY;

//     double pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

//     deltaX /= pixels;
//     deltaY /= pixels;

//     double pixelsX = beginX;
//     double pixelsY = beginY;
 
//     for(int i=0; i<pixels; i++){
//         mlx_pixel_put(main->mlx_p, main->mlx_win, pixelsX, pixelsY, color);

//         pixelsX+=deltaX;
//         pixelsY+=deltaY;
//         pixels--;
//     }
// }

void	raycasting(t_main *main)
{
	// RAY
	int x = 0;
	double cameraX = 0;
	double rayDirX = 0;
	double rayDirY = 0;
	double deltaDistX = 0;
	double deltaDistY = 0;
	int mapX = 0;
	int mapY = 0;
	double sideDistX = 0;
	double sideDistY = 0;
	int stepX = 0;
	int stepY = 0;
	int hit = 0;
	int side = 0;
	// LINE
	int wall_dist = 0;
	int lx = 0;
	int ly0 = 0;
	int ly1 = 0;
	double wall_x = 0;

	while (x < (main->map.w * 48))
	{
		cameraX = 2 * x / (double)main->map.w * 48 - 1;
		rayDirX = main->map.dirX + main->map.planeX * cameraX;
		rayDirY = main->map.dirY + main->map.planeY * cameraX;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		mapX = (int)main->map.p_pos_x;
		mapY = (int)main->map.p_pos_y;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (main->map.p_pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - main->map.p_pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
        	sideDistY = (main->map.p_pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
        	sideDistY = (mapY + 1.0 - main->map.p_pos_y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (main->map.grid[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			wall_dist = sideDistX - deltaDistX;
		else
			wall_dist = sideDistY - deltaDistY;
		lx = (int)((main->map.h * 48) / wall_dist);
		ly0 = -lx / 2 + (main->map.h * 48) / 2;
		if (ly0 < 0)
			ly0 = 0;
		ly1 = lx / 2 + (main->map.h * 48) / 2;
		if (ly1 >= (main->map.h * 48))
			ly1 = (main->map.h * 48) - 1;
		if (side == 0)
			wall_x = main->map.p_pos_y + wall_dist * main->map.dirY;
		else
			wall_x = main->map.p_pos_x + wall_dist * main->map.dirX;
		wall_x -= floor(wall_x);
		x++;
	}
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
		mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_p.img, main->map.p_pos_x, main->map.p_pos_y);
		// mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_angle.img, main->map.p_pos_x + main->map.DirX * 5, main->map.p_pos_y + main->map.DirY * 5);
		j++;
		px_w += 48;
	}
	raycasting(main);
}
