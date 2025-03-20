#include "../includes/cub3d.h"

void	free_grids(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->map.h)
	{
		free(main->map.grid[i]);
		free(main->map.highlight_grid[i]);
		i++;
	}
	free(main->map.grid);
	free(main->map.highlight_grid);
}

void free_textures(t_main *main)
{
	if (main->tex.NO)
		free(main->tex.NO);
	if (main->tex.SO)
		free(main->tex.SO);
	if (main->tex.WE)
		free(main->tex.WE);
	if (main->tex.EA)
		free(main->tex.EA);
}
