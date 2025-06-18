#include "../includes/cub3d.h"

char	get_debut_h(t_main *main, int i, int j)
{
	char	debut;

	if (j == 0)
		debut = '1';
	else
		debut = main->map.grid[i][j - 1];
	return (debut);
}

char	get_end_h(t_main *main, int i, int j)
{
	char	end;

	if (j == (main->map.diff_w[i] - 1) && main->map.grid[i][j] != '0')
		end = '1';
	else
		end = main->map.grid[i][j];
	return (end);
}

char	get_debut_v(t_main *main, int i, int j)
{
	char	debut;

	if (i == 0)
		debut = '1';
	else
		debut = main->map.grid[i - 1][j];
	return (debut);
}

char	get_end_v(t_main *main, int i, int j)
{
	char	end;

	if (i == (main->map.h - 1) && main->map.grid[i][j] != '0')
		end = '1';
	else
		end = main->map.grid[i][j];
	return (end);
}

void	full_map(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < main->map.h)
	{
		while (main->map.grid[i][j])
		{
			if (main->map.grid[i][j] == ' ')
				main->map.grid[i][j] = '1';
			j++;
		}
		j = 0;
		i++;
	}
}
