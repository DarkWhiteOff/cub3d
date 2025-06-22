/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:13:24 by tzizi             #+#    #+#             */
/*   Updated: 2025/06/04 13:13:24 by tzizi            ###   ########.fr       */
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

# define WHITE	0xFFFFFF
# define RED	0x00FF0000
# define GEEN	0x0000FF00
# define BLUE	0x000000FF
# define BLACK	000000

# define HEXA "0123456789ABCDEF"

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

typedef struct s_tex_data
{
	void	*img;
	char	*addr;
	int		b;
	int		ls;
	int		end;
	int		w;
	int		h;
}	t_tex_data;

typedef struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		color_f;
	int		color_c;
	int		map_start;
	t_tex_data	tex_north;
	t_tex_data	tex_south;
	t_tex_data	tex_west;
	t_tex_data	tex_east;
}	t_tex;

typedef struct s_ray
{
	float	fov;
	float	hfov;
	float	ray_angle;
	float	diff_ray_angle;
	float	precision;
	float	limit;
	float	cos;
	float	sin;
	t_d_pxy	d_ray_pos;
}	t_ray;

typedef struct s_map
{
	char		*path;
	int			h;
	int			w;
	int			px_h;
	int			px_w;
	int			*diff_w;
	int			w_max;
	int			player_pos;
	int			fd;
	char		**grid;
	int			z;
	int			q;
	int			s;
	int			d;
	int			left;
	int			right;
	t_px_pxy	px_player_pos;
	t_d_pxy		d_player_pos;
}	t_map;

typedef struct s_img_data
{
	char	*addr;
	int		b;
	int		ls;
	int		end;
}	t_img_data;

typedef struct s_main
{
	void		*mlx_p;
	void		*mlx_win;
	void		*img;
	t_img_data	img_data;
	t_pxy		p_pos;
	t_map		map;
	t_ray		ray;
	t_tex		tex;
	int			fd;
	int			fd1;
	int			fd2;
	int			fd3;
	int			empty_line;
	int			double_tex;
	t_sprite	spr_wall;
	t_sprite	spr_floor;
	t_sprite	spr_p;
}	t_main;

#endif