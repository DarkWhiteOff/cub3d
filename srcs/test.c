/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:40 by tzizi             #+#    #+#             */
/*   Updated: 2025/03/12 13:12:54 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define white 0xFFFFFF
# define red   0x00FF0000
# define green 0x0000FF00
# define blue  0x000000FF
# define black 000000

#include "../includes/cub3d.h"

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

float dist(float ax, float ay, float bx, float by)
{
    return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void drawRay(t_map map, t_main *main)
{
    int r;
    int mx;
    int my;
    int mp;
    int dof=0;
    float rx;
    float ry;
    float ra;
    float xo;
    float yo;
    float disT;


    ra = map.pos_a-DEG_TO_RAD*30;
    if (ra < 0)
        ra += 2*M_PI;
    if (ra > 2*M_PI)
        ra -= 2*M_PI;
    for(r=0; r<60;r++)
    {
        dof = 0;
        float disH=1000000;
        float hx = map.pixel_pos_x;
        float hy = map.pixel_pos_y;
        float aTan=-1/tan(ra);
        if (ra > M_PI) //looking down
        {
            ry = (int)map.pixel_pos_y - 0.0001;
            rx = (map.pixel_pos_y - ry) * aTan + map.pixel_pos_x;
            yo = -64;
            xo = -yo * aTan;
        }
        if (ra < M_PI) //looking up
        {
            ry = (int)map.pixel_pos_y + 64;
            rx = (map.pixel_pos_y - ry) * aTan + map.pixel_pos_x;
            yo = 64;
            xo = -yo * aTan;
        }
        if (ra == 0 || ra == M_PI) /// looking left or right
        {
            rx = map.pixel_pos_x;
            ry = map.pixel_pos_y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int) (rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * map.w + mx;
            if (mp > 0 && mp < map.w * map.h && map._map[mp] == 1)
            {
                hx = rx;
                hy = ry;
                disH = dist(map.pixel_pos_x, map.pixel_pos_y, hx, hy);
                dof = 8;
            }
            else // next step adding offset on x and y
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        drawLine(main, map.pixel_pos_x, map.pixel_pos_y, rx, ry, red);

        dof = 0;
        float disV=1000000;
        float vx = map.pixel_pos_x;
        float vy = map.pixel_pos_y;
        float nTan=-tan(ra);
        if (ra > PI2 && ra < PI3) //looking left
        {
            rx = (int)map.pixel_pos_x - 0.0001;
            ry = (map.pixel_pos_x - rx) * nTan + map.pixel_pos_y;
            xo = -64;
            yo = -xo * nTan;
        }
        if (ra < PI2 || ra > PI3) //looking right
        {
            rx = (int)map.pixel_pos_x + 64;
            ry = (map.pixel_pos_x - rx) * nTan + map.pixel_pos_y;
            xo = 64;
            yo = -xo * nTan;
        }
        if (ra == 0 || ra == M_PI) /// up or down
        {
            rx = map.pixel_pos_x;
            ry = map.pixel_pos_y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int) (rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * map.w + mx;
            if (mp > 0 && mp < map.w * map.h && map._map[mp] == 1)
            {
                vx = rx;
                vy = ry;
                disV = dist(map.pixel_pos_x, map.pixel_pos_y, vx, vy);
                dof = 8;
            }
            else // next step adding offset on x and y
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        if (disV < disH)
        {
            disT = disV;
            rx = vx;
            ry = vy;
        }
        if (disH > disV)
        {
            disT = disH;
            rx = hx;
            ry = hy;
        }
        drawLine(main, map.pixel_pos_x, map.pixel_pos_y, rx, ry, green);
        float ca = -map.pos_a - ra; // fisheye fix
        if (ca < 0)
            ca += 2*M_PI;
        if (ca > 2*M_PI)
            ca -= 2*M_PI;
        disT *= cos(ca);
        float lineH = ((map.w * map.h)*320/disT); // clalc line Height
        if (lineH>320)
            lineH=320;
        float lineO = 160 - lineH/2; // calc line offset
        int width = r*8+530;
        int height = (int)(lineH + lineO);
        if (mp > 0 && mp < map.w * map.h && map._map[mp] == 1)
            mlx_xpm_file_to_image(main->mlx_p, "../spr_tiles/spr_wall.xp", &width, &height);
        else
            mlx_xpm_file_to_image(main->mlx_p, "../spr_tiles/spr_floor.xp", &width, &height);
        //drawRect(r*8+530, lineH+lineO, red, 8);
        ra += DEG_TO_RAD;
        if (ra < 0)
        ra += 2*M_PI;
        if (ra > 2*M_PI)
            ra -= 2*M_PI;
    }
}