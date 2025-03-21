#include "../includes/cub3d.h"

void	my_mlx_pixel_put(void *img, char *adrr, int ls, int b, int x, int y, int color)
{
	char	*dst;

	(void)img;
	dst = adrr + (y * ls + x * (b / 8));
	*(unsigned int *)dst = color;
}

unsigned char	*add_char_to_str(unsigned char *s, unsigned char c, int _free)
{
	unsigned char	*res;
	int		len;
	int		i;

	len = unsigned_ft_strlen(s);
	res = malloc((len + 2) * sizeof(unsigned char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i++] = c;
	res[i++] = '\0';
	if (_free && s)
		free(s);
	printf("res %s\n s '%s' c '%c'\n", res, s, c);
	return (res);
}

int	find_pxtex_pos(t_main *main, int z, int wall_height, int ray_count, float *cy, float dy)
{
	(void)wall_height;
	(void)ray_count;
	(void)cy;
	// printf("%d\n", (((int)(cy[0] + dy) * main->map.px_w + z) / 64) / 64);
	unsigned char r=0;
	unsigned char g=0;
	unsigned char b=0;
	r = (unsigned char)main->tex.tex_east.addr[(int)(cy[0] + dy) * main->map.px_w + z + 2+];
	g = (unsigned char)main->tex.tex_east.addr[(int)(cy[0] + dy) * main->map.px_w + z + 3];
	b = (unsigned char)main->tex.tex_east.addr[(int)(cy[0] + dy) * main->map.px_w + z + 4];
	// printf("r %d g %d b %d\n", r, g, b);
	// printf("%s\n", ft_itoa(b));
	char *r1 = ft_strjoin(ft_itoa(r), ",");
	char *g1 = ft_strjoin(ft_itoa(g), ",");
	char *tmp = NULL;
	tmp = ft_strjoin(r1, g1);
	free(r1);
	free(g1);
	char  *str = NULL;
	str = ft_strjoin(tmp, ft_itoa(b));
	int color = rgbToHex(str);
	return (free(str), color);
}

void	draw_texture(t_main *main, int ray_count, int wall_height) //A refaire pour comprendre
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)main->tex.tex_north.w;
	ds = ((float)main->map.px_h / 2) - (float)wall_height;
	cy[1] = ds;
	z = -1;
	while (++z < main->tex.tex_north.w)
	{
		color = find_pxtex_pos(main, z, wall_height, ray_count, cy, dy);
		cy[0] = cy[1];
		while (cy[0] < cy[1] + dy)
		{
			if (cy[0] >= 0 && cy[0] < (float)main->map.px_h)
				my_mlx_pixel_put(&main->img, main->addr, main->ls, main->b, ray_count, cy[0], color);
			cy[0]++;
		}
		cy[1] += dy;
	}
}

void	raycasting(t_main *main)
{
	float distance = 0.0;
	float ray_angle = main->ray.ray_angle - main->ray.HFOV;
	int i = -1;
	int wall_h = 0;
	float ds = 0.0;
	int j = -1;

	while (++i < main->map.px_w)
	{
		//Ray end pos calculations
		main->ray.cos = cos(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.sin = sin(degree_to_radians(ray_angle)) / main->ray.precision;
		main->ray.d_ray_pos.x = main->map.d_player_pos.x + 0.5;
		main->ray.d_ray_pos.y = main->map.d_player_pos.y + 0.5;
		while (!ft_strchr("1", main->map.grid[(int)main->ray.d_ray_pos.y][(int)main->ray.d_ray_pos.x]) && \
			sqrt(powf(main->ray.d_ray_pos.x - main->map.d_player_pos.x - 0.5, 2.0) + \
			powf(main->ray.d_ray_pos.y - main->map.d_player_pos.y - 0.5, 2.0)) < main->ray.limit)
		{
			
			main->ray.d_ray_pos.x += main->ray.cos;
			main->ray.d_ray_pos.y += main->ray.sin;
		}
		//Wall height calculations
		distance = sqrt(powf(main->ray.d_ray_pos.x - main->map.d_player_pos.x - 0.5, 2.0) + powf(main->ray.d_ray_pos.y - main->map.d_player_pos.y - 0.5, 2.0));
		distance = distance * cos(degree_to_radians(ray_angle - main->ray.ray_angle));	
		wall_h = (int)(main->map.px_h / (1.5 * distance));
		ds = ((float)main->map.px_h / 2) - (float)wall_h;
		//Put pixels on img (not window)
		j = -1;
		while (++j < main->map.px_h)
		{
			if (j < ds)
				my_mlx_pixel_put(&main->img, main->addr, main->ls, main->b, i, j, main->tex.color_c); //Ceiling
			else if (j >= (main->map.px_h / 2) + wall_h)
				my_mlx_pixel_put(&main->img, main->addr, main->ls, main->b, i, j, main->tex.color_f); //Floor
		}
		//Complexe mais la fonction dessine les murs sur l'img
		draw_texture(main, i, wall_h);
		ray_angle += main->ray.diff_ray_angle;
	}
}

int	game_refresh(t_main *main)
{
	actualise_player(main); // MOVES
	raycasting(main); // RAYCAST
	mlx_put_image_to_window(main->mlx_p, main->mlx_win, main->img, 0, 0); // REFRESH IMG
	return (0);
}
