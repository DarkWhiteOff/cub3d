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
		if (check == 1)
			raycasting(main);
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
	double wall_x = 0;

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
		wall_x = 0;

		cameraX = 2 * x / ((double)main->map.w * 48) - 1;
		rayDirX = main->map.dirX + main->map.planeX * cameraX;
		rayDirY = main->map.dirY + main->map.planeY * cameraX;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		mapX = (int)main->map.p_pos_x / 48;
		mapY = (int)main->map.p_pos_y / 48;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (main->map.p_pos_x / 48 - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - main->map.p_pos_x / 48) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
        	sideDistY = (main->map.p_pos_y / 48 - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
        	sideDistY = (mapY + 1.0 - main->map.p_pos_y / 48) * deltaDistY;
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
			printf("mapX : %d | mapY : %d\n", mapX, mapY);
			printf("main->map.grid[mapY][mapX] : %c\n", main->map.grid[mapY][mapX]);
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
		if (side == 0)
			wall_x = main->map.p_pos_y / 48 + wall_dist * rayDirY;
		else
			wall_x = main->map.p_pos_x / 48 + wall_dist * rayDirX;
		wall_x -= floor(wall_x);
		// int color = green;
        // drawLine(main, x, ly0, x, ly1, color);
		
	int			y = 0;
	int			color = 0;

	if (side == 0)
	{
		if (rayDirX < 0)
			main->texinfo.index = WEST;
		else
			main->texinfo.index = EAST;
	}
	else
	{
		if (rayDirY > 0)
			main->texinfo.index = SOUTH;
		else
			main->texinfo.index = NORTH;
	}
	main->texinfo.x = (int)(wall_x * main->texinfo.size);
	if ((side == 0 && rayDirX < 0)
		|| (side == 1 && rayDirY > 0))
		main->texinfo.x = main->texinfo.size - main->texinfo.x - 1;
	main->texinfo.step = 1.0 * main->texinfo.size / lh;
	main->texinfo.pos = (ly0 - (main->map.h * 48) / 2
			+ lh / 2) * main->texinfo.step;
	y = ly0;
	while (y < ly1)
	{
		main->texinfo.y = (int)main->texinfo.pos & (main->texinfo.size - 1);
		main->texinfo.pos += main->texinfo.step;
		color = green; // data->textures[main->texinfo.index][main->texinfo.size * main->texinfo.y + main->texinfo.x];
		if (main->texinfo.index == NORTH || main->texinfo.index == EAST)
			color = (color >> 1) & 8355711;
		// if (color > 0)
		// 	data->texture_pixels[y][x] = color;
		y++;
	}
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
}
