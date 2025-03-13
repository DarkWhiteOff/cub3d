#include "../includes/cub3d.h"

int	game_refresh(t_main *main)
{
	int	i;
	int	px_h;
	static int check;

	i = 0;
	px_h = 0;
	//printf("z : %d\n", main->map.z);
	if (main->map.z == 1 || main->map.q == 1 || main->map.s == 1 || main->map.d == 1 || main->map.left == 1 || main->map.right == 1 || check == 0)
	{
		put_to_zero(&main->map);
		while (i < main->map.h)
		{
			update_map(main, i, px_h, check);
			i++;
			px_h += 48;
		}

		check = 1;
	}
	return (0);
}

void drawLine(t_main *main, int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX = endX - beginX;
    double deltaY = endY - beginY;

    double pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

    deltaX /= pixels;
    deltaY /= pixels;

    double pixelsX = beginX;
    double pixelsY = beginY;
 
    for(int i=0; i<pixels; i++){
        mlx_pixel_put(main->mlx_p, main->mlx_win, pixelsX, pixelsY, color);

        pixelsX+=deltaX;
        pixelsY+=deltaY;
        pixels--;
    }
}

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
	int lh = 0;
	int ly0 = 0;
	int ly1 = 0;
	// double wall_x = 0;

	while (x < (main->map.w * 48))
	{
		cameraX = 0;
		rayDirX = 0;
		rayDirY = 0;
		deltaDistX = 0;
		deltaDistY = 0;
		mapX = 0;
		mapY = 0;
		sideDistX = 0;
		sideDistY = 0;
		stepX = 0;
		stepY = 0;
		hit = 0;
		side = 0;
		wall_dist = 0;
		lh = 0;
		ly0 = 0;
		ly1 = 0;
		// wall_x = 0;

		cameraX = 2 * x / ((double)main->map.w * 48) - 1;
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
		hit = 0;
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
			printf("mapX : %d (%d) | mapY : %d (%d)\n", mapX, mapX / 48, mapY, mapY / 48);
			printf("main->map.grid[mapY / 48][mapX / 48] : %c\n", main->map.grid[mapY / 48][mapX / 48]);
			if (mapY < 0.25
				|| mapX < 0.25
				|| mapY > main->map.h - 0.25
				|| mapX > main->map.w - 1.25)
				break ;
			else if (main->map.grid[mapY / 48][mapX / 48] > '0')
				hit = 1;
		}
		if (side == 0)
			wall_dist = sideDistX - deltaDistX;
		else
			wall_dist = sideDistY - deltaDistY;
		if (wall_dist == 0)
			wall_dist = 1;
		lh = (int)((main->map.h * 48) / wall_dist);
		ly0 = -lh / 2 + (main->map.h * 48) / 2;
		ly1 = lh / 2 + (main->map.h * 48) / 2;
		if (ly0 < 0)
			ly0 = 0;
		if (ly1 >= (main->map.h * 48))
			ly1 = (main->map.h * 48) - (1 * 48);
		// if (side == 0)
		// 	wall_x = main->map.p_pos_y + wall_dist * rayDirY;
		// else
		// 	wall_x = main->map.p_pos_x + wall_dist * rayDirX;
		// wall_x -= floor(wall_x);
        //drawLine(main, x, ly0, x, ly1, color);
		x++;
	}
}

void	update_map(t_main *main, int i, int px_h, int check)
{
	int	j;
	int	px_w;

	j = 0;
	px_w = 0;
	(void)check;
	while (main->map.grid[i][j] != '\0')
	{
		if (main->map.grid[i][j] == '1')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_wall.img, px_w, px_h);
		if (main->map.grid[i][j] == '0')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_floor.img, px_w, px_h);
		j++;
		px_w += 48;
	}
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_p.img, main->map.p_pos_x, main->map.p_pos_y);
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_angle.img, main->map.p_pos_x + main->map.dirX * 15, main->map.p_pos_y + main->map.dirY * 15);
	if (check == 1)
		raycasting(main);
}
