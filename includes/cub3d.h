#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "struct.h"

// CUB3D
void    render_init(t_main *main);
int     check_map_name(char *map_name);
void	checks_inits(t_main *main);
void	get_screen_size(t_map *map);
void	vars_init(t_main *main, char *map_path);
void	empty_line_check(char *line, int fd);
void	get_infos(t_main *main);
void	parse_map(t_main *main);
void	check_walls1(t_map *map);
void	check_walls2(t_map *map);
int     check_other_char(t_map *map, int y, int x);
void	is_epc(t_main *main, int i, int j, t_pxy *p_pos);
void	check_epc(t_main *main, t_pxy *p_pos);
void	check_path(t_map *map, int x, int y);
void	allocate_grids(t_map *map);
void	grid_init(t_main *main);
void	free_grids(t_map *map);
int     strlenmap(char *line);
void	check_fd_error(t_main *main);
void	sprites_init(t_main *main);
void	free_sprites(t_main *main);
void	update_player_pos(t_main *main, char c);
void	actualise_player(t_main *main);
void	move(float angle, t_main *main);
int     key_manager_down(int keycode, t_main *main);
int     key_manager_up(int keycode, t_main *main);
int     close_window(t_main *main);
int     game_refresh(t_main *main);
void	raycasting(t_main *main);
void	draw_texture(t_main *main, int ray_count, int wall_height);
void	my_mlx_pixel_put(void *img, char *adrr, int ls, int b, int x, int y, int color);
float	degree_to_radians(float degree);

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