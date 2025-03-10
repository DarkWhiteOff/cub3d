#include "../includes/cub3d.h"

void	checks_inits(t_main *main)
{
	parse_map(&main->map);
	grid_init(main);
	check_walls1(&main->map);
	check_walls2(&main->map);
	check_epc(&main->map, &main->p_pos);
	check_path(&main->map, main->p_pos.x, main->p_pos.y);
	main->map.grid[main->e_pos.y][main->e_pos.x] = '0';
	if (main->map.exit_acc != 1 || main->map.coll_acc != main->map.coll)
	{
		free_grids(&main->map);
		exit (ft_printf("Error\nExit or collectibles aren't accessible.\n"));
	}
}

int	main(void)
{
	t_main	main;

    checks_inits(&main);
	return (0);
}
