/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zz <zz@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:44 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/16 18:50:33 by zz               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_walls1half(t_main *main, int param)
{
	int	i;

	i = 0;
	while (i < main->map.diff_w[param])
	{
		while (main->map.grid[param][i] == ' ')
			i++;
		if (main->map.grid[param][i] != '1' && (main->map.grid[param][i] != ' '
			&& i < main->map.diff_w[param]))
		{
			free(main->map.diff_w);
			free_textures(main);
			free_grids(main);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
}

void	check_walls1(t_main *main)
{
	check_walls1half(main, 0);
	check_walls1half(main, main->map.h - 1);
}

void	check_walls2(t_main *main)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < main->map.h - 1)
	{
		while (main->map.grid[i][j] == ' ')
			j++;
		if (main->map.grid[i][j] != '1'
			|| main->map.grid[i][main->map.diff_w[i] - 1] != '1')
		{
			free(main->map.diff_w);
			free_textures(main);
			free_grids(main);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		j = 0;
		i++;
	}
}

void	check_path(t_main *main, int x, int y)
{
	if (main->map.grid[y][x] == ' ')
	{
		free(main->map.diff_w);
		free_textures(main);
		exit(printf("Error\nMap not closed.\n"));
	}
	if (main->map.grid[y][x] == '1' || main->map.highlight_grid[y][x] == '1'
		|| x < 0 || y < 0 || x > main->map.diff_w[y] || y > main->map.h)
		return ;
	main->map.highlight_grid[y][x] = '1';
	check_path(main, x - 1, y);
	check_path(main, x + 1, y);
	check_path(main, x, y - 1);
	check_path(main, x, y + 1);
	return ;
}
