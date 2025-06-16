/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zz <zz@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:44 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/16 22:39:54 by zz               ###   ########.fr       */
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
				if (j == 0)
				{
					printf("i : %d | j : %d\n", i, j);
					debut = '1';
				}
				else
				{
					printf("i : %d | j : %d\n", i, j - 1);
					debut = main->map.grid[i][j - 1];
				}
				while (main->map.grid[i][j] == ' ' && i < main->map.diff_w[i])
					j++;
				printf("i : %d | j : %d\n", i, j);
				if (j == (main->map.diff_w[i] - 1) && main->map.grid[i][j] != '0')
					end = '1';
				else
					end = main->map.grid[i][j];
				printf("debut : %c | end : %c\n", debut, end);
				if (debut != '1' || end != '1')
				{
					free(main->map.diff_w);
					free_textures(main);
					free_grids(main);
					exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
				}
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
				if (i == 0)
					debut = '1';
				else
					debut = main->map.grid[i - 1][j];
				while (main->map.grid[i][j] == ' ' && i < main->map.h - 1)
					i++;
				if (i == (main->map.h - 1) && main->map.grid[i][j] != '0')
					end = '1';
				else
					end = main->map.grid[i][j];
				if (debut != '1' || end != '1')
				{
					free(main->map.diff_w);
					free_textures(main);
					free_grids(main);
					exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
				}
			}
			i++;
		}
		i = 0;
		j++;
	}
}
