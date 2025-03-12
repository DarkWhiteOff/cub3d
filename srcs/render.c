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

void drawLine(t_main *main, double beginX, double beginY, double endX, double endY, int color)
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

void	drawRay(t_main *main)
{
	int r = 0;
	int mx = 0;
	int my = 0;
	int mp = 0;
	int dof = 0;
	float rx = 0;
	float ry = 0;
	float ra = 0;
	float xo = 0;
	float yo = 0;

	ra = main->map.pos_a;
	for (r = 0; r < 1; r++)
	{
		dof = 0;
		float aTan = 1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int) main->map.pixel_pos_y / 48) * 48) - 0.0001;
			rx = (main->map.pixel_pos_y - ry) * aTan + main->map.pixel_pos_x;
			yo = -48;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int) main->map.pixel_pos_y / 48) * 48) + 48;
			rx = (main->map.pixel_pos_y - ry) * aTan + main->map.pixel_pos_x;
			yo = 48;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = main->map.pixel_pos_x;
			ry = main->map.pixel_pos_y;
			dof = 15;
		}
		while (dof < 15)
		{
			mx = (int) (rx) / 48;
			my = (int) (ry) / 48;
			mp = my * main->map.w + mx;
			if (mp > 0 && (mp < (main->map.w * main->map.h)) && main->map.grid[mp] != NULL)
				dof = 15;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		drawLine(main, main->map.pixel_pos_x, main->map.pixel_pos_y, rx, ry, 0x0000FF00);
	}
}

void	update_map(t_main *main, int i, int px_h)
{
	int	j;
	int	px_w;

	j = 0;
	px_w = 0;
	if (main->map.z == 1 || main->map.q == 1 || main->map.s == 1 || main->map.d == 1 || main->map.left == 1 || main->map.right == 1)
	{
		if (main->map.z == 1)
		{
			main->map.pixel_pos_x += main->map.pos_dx;
			main->map.pixel_pos_y += main->map.pos_dy;
		}
		else if (main->map.q == 1)
			main->map.pixel_pos_x = main->map.pixel_pos_x - 10;
		else if (main->map.s == 1)
		{
			main->map.pixel_pos_x -= main->map.pos_dx;
			main->map.pixel_pos_y -= main->map.pos_dy;
		}
		else if (main->map.d == 1)
			main->map.pixel_pos_x = main->map.pixel_pos_x + 10;
		else if (main->map.left == 1)
		{
			main->map.pos_a -= 0.1;
			if (main->map.pos_a < 0)
				main->map.pos_a += (2 * PI);
			main->map.pos_dx = cos(main->map.pos_a) * 5;
			main->map.pos_dy = sin(main->map.pos_a) * 5;
		}
		else if (main->map.right == 1)
		{
			main->map.pos_a += 0.1;
			if (main->map.pos_a > (2 * PI))
				main->map.pos_a -= (2 * PI);
			main->map.pos_dx = cos(main->map.pos_a) * 5;
			main->map.pos_dy = sin(main->map.pos_a) * 5;
		}
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
		mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_angle.img, main->map.pixel_pos_x + main->map.pos_dx * 5, main->map.pixel_pos_y + main->map.pos_dy * 5);
		j++;
		px_w += 48;
	}
	drawRay(main);
}
