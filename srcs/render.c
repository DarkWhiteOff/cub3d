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
	if (main->map.z == 1 || main->map.q == 1 || main->map.s == 1 || main->map.d == 1 || main->map.left == 1 || main->map.right == 1)
	{
		if (main->map.z == 1)
		{
			main->map.pixel_pos_x -= main->map.pos_dx;
			main->map.pixel_pos_y -= main->map.pos_dy;
		}
		else if (main->map.q == 1)
			main->map.pixel_pos_x = main->map.pixel_pos_x - 10;
		else if (main->map.s == 1)
		{
			main->map.pixel_pos_x += main->map.pos_dx;
			main->map.pixel_pos_y += main->map.pos_dy;
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
	main->map.ra = main->map.pos_a;
	for (main->map.r = 0; main->map.r < 1; main->map.r++)
	{
		main->map.dof = 0;
		float aTan = 1 / tan(main->map.ra);
		if (main->map.ra > PI)
		{
			main->map.ry = (((int) main->map.pixel_pos_y / 48) * 48) - 0.0001;
			main->map.rx = (main->map.pixel_pos_y - main->map.ry) * aTan + main->map.pixel_pos_x;
			main->map.yo = -48;
			main->map.xo = -main->map.yo * aTan;
		}
		if (main->map.ra < PI)
		{
			main->map.ry = (((int) main->map.pixel_pos_y / 48) * 48) + 48;
			main->map.rx = (main->map.pixel_pos_y - main->map.ry) * aTan + main->map.pixel_pos_x;
			main->map.yo = 48;
			main->map.xo = -main->map.yo * aTan;
		}
		if (main->map.ra == 0 || main->map.ra == PI)
		{
			main->map.rx = main->map.pixel_pos_x;
			main->map.ry = main->map.pixel_pos_y;
			main->map.dof = 15;
		}
		while (main->map.dof < 15)
		{
			main->map.mx = (int) (main->map.rx) / 48;
			main->map.my = (int) (main->map.ry) / 48;
			main->map.mp = main->map.my * main->map.w + main->map.mx;
			if ((main->map.mp < (main->map.w * main->map.h)) && main->map.grid[main->map.mp] != NULL)
				main->map.dof = 15;
			else
			{
				main->map.rx += main->map.xo;
				main->map.ry += main->map.yo;
				main->map.dof += 1;
			}
		}
		mlx_put_i
	}
	drawLine(main, main->map.pixel_pos_x, main->map.pixel_pos_y, main->map.rx, main->map.ry, );
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