/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:44 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/18 14:45:52 by zamgar           ###   ########.fr       */
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

void	check_horizontal(t_main *main)
{
	int	i;
	int	j;
	char debut;
	char end;

	i = 1;
	j = 0;
	while (i < main->map.h - 1)
	{
		while (j < main->map.diff_w[i])
		{
			if (main->map.grid[i][j] == ' ')
			{
				debut = get_debut_h(main, i, j);
				while (main->map.grid[i][j] == ' ' && i < main->map.diff_w[i])
					j++;
				end = get_end_h(main, i, j);
				if (debut != '1' || end != '1')
					free_diff_tex_grids(main, 1);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	check_vertical(t_main *main)
{
	int	i;
	int	j;
	char debut;
	char end;

	i = 0;
	j = 1;
	while (j < main->map.w_max - 1)
	{
		while (i < main->map.h)
		{
			if (main->map.grid[i][j] == ' ')
			{
				debut = get_debut_v(main, i, j);
				while (main->map.grid[i][j] == ' ' && i < main->map.h - 1)
					i++;
				end = get_end_v(main, i, j);
				if (debut != '1' || end != '1')
					free_diff_tex_grids(main, 1);
			}
			i++;
		}
		i = 0;
		j++;
	}
}
