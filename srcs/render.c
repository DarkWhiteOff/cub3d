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
		main->map.ra = main->map.pos_a;
		for (main->map.r = 0; main->map.r < 1; main->map.r++)
		{
			main->map.dof = 0;
			float aTan = 1 / tan(main->map.ra);
			if (main->map.ra > PI)
			{
				main->map.ry = (((int) main->map.pixel_pos_y >> 6) << 6) - 0.0001;
				main->map.rx = (main->map.pixel_pos_y - main->map.ry) * aTan + main->map.pixel_pos_x;
				main->map.yo = -64;
				main->map.xo = -main->map.yo * aTan;
			}
			if (main->map.ra < PI)
			{
				main->map.ry = (((int) main->map.pixel_pos_y >> 6) << 6) + 64;
				main->map.rx = (main->map.pixel_pos_y - main->map.ry) * aTan + main->map.pixel_pos_x;
				main->map.yo = 64;
				main->map.xo = -main->map.yo * aTan;
			}
			if (main->map.ra == 0 || main->map.ra == PI)
			{
				main->map.rx = main->map.pixel_pos_x;
				main->map.ry = main->map.pixel_pos_y;
				main->map.dof = 8;
			}
			while (main->map.dof < 8)
			{
				main->map.mx = (int) (main->map.rx) >> 6;
				main->map.my = (int) (main->map.ry) >> 6;
				main->map.mp = main->map.my * main->map.w + main->map.mx;
				if ((main->map.mp < (main->map.w * main->map.h)) && main->map.grid[main->map.mp] != NULL)
					main->map.dof = 8;
				else
				{
					main->map.rx += main->map.xo;
					main->map.ry += main->map.yo;
					main->map.dof += 1;
				}
			}
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
		j++;
		px_w += 48;
	}
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_p.img, main->map.pixel_pos_x, main->map.pixel_pos_y);
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->spr_angle.img, main->map.pixel_pos_x + main->map.pos_dx * 5, main->map.pixel_pos_y + main->map.pos_dy * 5);
	draw_line(main, main->map.pixel_pos_x, main->map.pixel_pos_y, main->map.rx, main->map.ry, 0x0000FF00);	
	// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.pixel_pos_x, main->map.pixel_pos_y, 7);
		// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.pixel_pos_x + 1, main->map.pixel_pos_y, 7);
		// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.pixel_pos_x + 1, main->map.pixel_pos_y - 1, 7);
		// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.pixel_pos_x, main->map.pixel_pos_y - 1, 7);

		// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.rx, main->map.ry, 7);
		// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.rx + 1, main->map.ry, 7);
		// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.rx + 1, main->map.ry - 1, 7);
		// mlx_pixel_put(main->mlx_p, main->mlx_win, main->map.rx, main->map.ry - 1, 7);
}

void    mlx_pixel_put_custom(t_main *main, int x, int y, int color)
{
    mlx_pixel_put(main->mlx_p, main->mlx_win, x, y, color);
}

void    draw_line(t_main *main, int x1, int y1, int x2, int y2, int color)
{
    int dx, dy, p, x, y, x_end, y_end;

    dx = x2 - x1;
    dy = y2 - y1;
    x = x1;
    y = y1;
    
    // Calculate which point is the end point (the one with higher x or y value)
    x_end = x2;
    y_end = y2;
    if (dx < 0) {
        dx = -dx;
        x = x2;
        x_end = x1;
    }
    if (dy < 0) {
        dy = -dy;
        y = y2;
        y_end = y1;
    }
    
    // Bresenham's line algorithm
    if (dx > dy) {
        p = 2 * dy - dx;
        while (x != x_end) {
            mlx_pixel_put_custom(main, x, y, color);
            if (p >= 0) {
                y += (y2 > y1) ? 1 : -1;
                p -= 2 * dx;
            }
            p += 2 * dy;
            x += (x2 > x1) ? 1 : -1;
        }
    } else {
        p = 2 * dx - dy;
        while (y != y_end) {
            mlx_pixel_put_custom(main, x, y, color);
            if (p >= 0) {
                x += (x2 > x1) ? 1 : -1;
                p -= 2 * dy;
            }
            p += 2 * dx;
            y += (y2 > y1) ? 1 : -1;
        }
    }
    mlx_pixel_put_custom(main, x, y, color); // Draw the final point
}