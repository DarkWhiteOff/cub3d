/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeezou <zeezou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:27 by zamgar            #+#    #+#             */
/*   Updated: 2025/04/12 08:52:29 by zeezou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "struct.h"

// CUB3D
void	render_init(t_main *main);
void	checks_inits(t_main *main);
void	vars_init(t_main *main, char *map_path);
void    tex_init (t_tex *tex);
void    ray_init (t_ray *ray);
void    map_init (t_map *map, char *map_path);
void	get_infos(t_main *main);
void    get_diff_width(t_main *main);
int     check_w(int *array);
void	parse_map(t_main *main);
void	check_walls1(t_main *main);
void	check_walls2(t_main *main);
void	check_path(t_main *main, int x, int y);
void	is_epc(t_main *main, int i, int j, t_pxy *p_pos);
int     check_other_char(t_map *map, int y, int x);
void	check_epc(t_main *main, t_pxy *p_pos);
void	allocate_grids(t_map *map);
void	grid_init(t_main *main);
int     get_index_hex(char c);
int     get_rgb(char *line, int rgb);
int     rgbToHex(char *line);
void	free_grids(t_main *main);
void    free_textures(t_main *main);
int	    key_manager_up(int keycode, t_main *main);
int	    key_manager_down(int keycode, t_main *main);
void	actualise_player(t_main *main);
void	move(float angle, t_main *main);
int	    close_window(t_main *main);
int	    game_refresh(t_main *main);
void	raycasting(t_main *main);
void	draw_texture(t_main *main, int ray_count, int wall_height);
void	my_mlx_pixel_put(char *adrr, int ls, int b, int x, int y, int color);
void	empty_line_check(t_main *main, char *line, int fd);
void	check_fd_error(t_main *main, int fd);
int	    strlenmap(char *line);
int	    check_map_name(char *map_name);
float	degree_to_radians(float degree);
void	sprites_init(t_main *main);
void	free_sprites(t_main *main);
void free_diff_tex_grids(t_main *main);

// GET_NEXT_LINE - LIBFT
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
int		ft(const char *s, unsigned char c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *str, unsigned int start, size_t len);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned char	*unsigned_ft_strjoin(unsigned char const *s1, unsigned char const *s2);
int	unsigned_ft_strlen(unsigned const char *s);

// FT_PRINTF
int		ft_printf(const char *str, ...);
int		get_next_arg(va_list *ap, char c);
int		ft_dec_into_hex(unsigned int n, int b);
void	ft_print_array(char *array, int i);
char	*ft_fill_hexarray(unsigned int n, char *string, char *array);
int		ft_get_size_hexarray(unsigned int n);
int		ft_itoa2(int n);
char	*ft_itoa(int n);
char	*ft_min(char *str);
int		ft_count(int n);
int		ft_unsigned_itoa2(unsigned int n);
char	*ft_unsigned_itoa(unsigned int n);
int		ft_unsigned_count(unsigned int n);
int		ft_putptr(unsigned long long adress);
char	*ft_fill_ptrarray(unsigned long long adress, char *string, char *array);
int		ft_get_size_ptrarray(unsigned long long adress);
int		ft_putstr(char *str);
int		ft_putchar(char c);
int		ft_strlen(const char *s);

#endif