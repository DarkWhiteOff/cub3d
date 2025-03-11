#include "../includes/cub3d.h"

int	close_window(t_main *main)
{
	mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	mlx_destroy_image(main->mlx_p, main->spr_coll.img);
	mlx_destroy_image(main->mlx_p, main->spr_door.img);
	mlx_destroy_image(main->mlx_p, main->spr_p.img);
	mlx_destroy_image(main->mlx_p, main->img);
	mlx_destroy_window(main->mlx_p, main->mlx_win);
	mlx_destroy_display(main->mlx_p);
	free(main->mlx_p);
	free_grids(&main->map);
	exit (ft_printf("Windows was killed.\n"));
}

// int	key_manager(int keycode, t_main *main)
// {
// 	if (keycode == 53 || keycode == 65307)
// 		close_window(main);
// 	if (keycode == 122) // 119
// 		update_player_pos(main, 'Z');
// 	if (keycode == 113) // 97
// 		update_player_pos(main, 'Q');
// 	if (keycode == 115)
// 		update_player_pos(main, 'S');
// 	if (keycode == 100)
// 		update_player_pos(main, 'D');
// 	return (0);
// }

// void	actualise_map_data(t_main *main)
// {
// 	int	x;
// 	int	y;

// 	x = main->p_pos.x;
// 	y = main->p_pos.y;
// 	main->map.grid[y][x] = 'P';
// }

// void	update_player_pos(t_main *main, char c)
// {
// 	main->map.grid[main->p_pos.y][main->p_pos.x] = '0';
// 	if (c == 'Z' && main->map.grid[main->p_pos.y - 1][main->p_pos.x] != '1')
// 		main->p_pos.y = main->p_pos.y - 1;
// 	if (c == 'Q' && main->map.grid[main->p_pos.y][main->p_pos.x - 1] != '1')
// 		main->p_pos.x = main->p_pos.x - 1;
// 	if (c == 'S' && main->map.grid[main->p_pos.y + 1][main->p_pos.x] != '1')
// 		main->p_pos.y = main->p_pos.y + 1;
// 	if (c == 'D' && main->map.grid[main->p_pos.y][main->p_pos.x + 1] != '1')
// 		main->p_pos.x = main->p_pos.x + 1;
// 	actualise_map_data(main);
// }

void	put_to_zero(t_map *map)
{
		map->z = 0;
		map->q = 0;
		map->s = 0;
		map->d = 0;
}

int	key_manager(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == 65307)
		close_window(main);
	if (keycode == 122) // 119
		main->map.z = 1;
	if (keycode == 113) // 97
		main->map.q = 1;
	if (keycode == 115)
		main->map.s = 1;
	if (keycode == 100)
		main->map.d = 1;
	return (0);
}