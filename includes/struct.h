/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:12:52 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 20:19:35 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <math.h>

# define PI 3.1415926535

# define white 0xFFFFFF
# define red   0x00FF0000
# define green 0x0000FF00
# define blue  0x000000FF
# define black 000000

typedef struct s_pxy
{
	int	x;
	int	y;
}	t_pxy;

typedef struct s_px_pxy
{
	size_t	x;
	size_t	y;
}	t_px_pxy;

typedef struct s_d_pxy
{
	float	x;
	float	y;
}	t_d_pxy;

typedef struct s_sprite
{
	int		w;
	int		h;
	void	*img;
}	t_sprite;

typedef struct s_img_i
{
	void		*img;
	char		*addr;
	int			b;
	int			ls;
	int			end;
	int			w;
	int			h;
}	t_img_i;

typedef struct s_tex
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int color_f;
	int color_c;
	int map_start;
	t_img_i tex_north;
	t_img_i tex_south;
	t_img_i tex_west;
	t_img_i tex_east;
}	t_tex;

typedef struct s_ray
{
	float FOV;
	float HFOV;
	float ray_angle;
	float	diff_ray_angle;
	float precision;
	float limit;
	float cos;
	float sin;
	t_d_pxy d_ray_pos;
}	t_ray;

typedef struct s_map
{
	//Checks
	char	*path;
	int		h;
	int		w;
	int		px_h;
	int		px_w;
	int		*diff_w;
	int		player_pos;
	int		fd;
	char	**grid;
	char	**highlight_grid;
	//Controls
	int			z;
	int			q;
	int			s;
	int			d;
	int			left;
	int			right;
	//Pos
	t_px_pxy px_player_pos;
	t_d_pxy d_player_pos;
}	t_map;

typedef struct s_main
{
	//Mlx
	void		*mlx_p;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			b;
	int			ls;
	int			end;
	//Map
	t_map		map;
	t_ray		ray;
	t_tex		tex;
	t_pxy		p_pos;
	//Sprites
	t_sprite	spr_wall;
	t_sprite	spr_floor;
	t_sprite	spr_angle;
	t_sprite	spr_p;
	int fd;
	int fd1;
	int fd2;
	int fd3;
	// int *tex_buf[1];
}	t_main;

#endif