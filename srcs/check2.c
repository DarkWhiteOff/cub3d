/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:46 by zamgar            #+#    #+#             */
/*   Updated: 2025/05/01 14:11:14 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	is_epc(t_main *main, int i, int j, t_pxy *p_pos)
{
	if (main->map.grid[i][j] == 'N'
		|| main->map.grid[i][j] == 'S'
		|| main->map.grid[i][j] == 'W'
		|| main->map.grid[i][j] == 'E')
	{
		main->map.player_pos++;
		p_pos->x = j;
		p_pos->y = i;
		if (main->map.grid[i][j] == 'N')
			main->ray.ray_angle = 90;
		if (main->map.grid[i][j] == 'S')
			main->ray.ray_angle = 270;
		if (main->map.grid[i][j] == 'W')
			main->ray.ray_angle = 180;
		if (main->map.grid[i][j] == 'E')
			main->ray.ray_angle = 0;
	}
}

int	check_other_char(t_map *map, int y, int x)
{
	if (map->grid[y][x] == 'N')
		return (0);
	if (map->grid[y][x] == 'S')
		return (0);
	if (map->grid[y][x] == 'W')
		return (0);
	if (map->grid[y][x] == 'E')
		return (0);
	if (map->grid[y][x] == '0')
		return (0);
	if (map->grid[y][x] == '1')
		return (0);
	if (map->grid[y][x] == ' ')
		return (0);
	return (1);
}

void	check_epc(t_main *main, t_pxy *p_pos)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < main->map.h - 1)
	{
		while (main->map.grid[i][j] != '\0')
		{
			is_epc(main, i, j, p_pos);
			if (check_other_char(&main->map, i, j) == 1)
			{
				free_diff_tex_grids(main);
				exit (ft_printf("Error\nMap contains unrecognized character.\n"));
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (main->map.player_pos != 1)
	{
		free_diff_tex_grids(main);
		exit (ft_printf("Error\nNo player position.\n"));
	}
}

void	allocate_grids(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->grid = (char **)malloc(sizeof(char *) * map->h + 1);
	map->highlight_grid = (char **)malloc(sizeof(char *) * map->h + 1);
	while (i < map->h)
	{
		map->grid[i] = (char *)malloc(sizeof(char) * (map->diff_w[i] + 1));
		map->highlight_grid[i] = (char *)malloc(sizeof(char)
				* (map->diff_w[i] + 1));
		i++;
	}
	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->diff_w[i])
		{
			map->highlight_grid[i][j] = '0';
			j++;
		}
		map->highlight_grid[i][j] = '\0';
		i++;
	}
}

void	grid_init(t_main *main)
{
	char	*line;
	int		j;
	int		i;

	i = 0;
	j = 0;
	main->fd3 = open(main->map.path, O_RDONLY);
	check_fd_error(main, main->fd3);
	line = get_next_line(main->fd3);
	while (main->tex.map_start--)
	{
		free(line);
		line = get_next_line(main->fd3);
	}
	allocate_grids(&main->map);
	while (i < main->map.h)
	{
		while (j < main->map.diff_w[i])
			main->map.grid[i][j++] = line[j];
		main->map.grid[i++][j] = '\0';
		j = 0;
		free(line);
		line = get_next_line(main->fd3);
	}
	close(main->fd3);
}
