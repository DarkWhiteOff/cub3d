/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:15 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/24 14:32:57 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	degree_to_radians(float degree)
{
	return (degree * PI / 180);
}

int	check_map_name(char *map_name)
{
	int	i;

	i = 0;
	while (map_name[i] != '\0')
		i++;
	if (map_name[i - 1] == 'b' && map_name[i - 2] == 'u'
		&& map_name[i - 3] == 'c' && map_name[i - 4] == '.'
		&& (map_name[i - 5] != '/' && map_name[i - 5] != 0))
		return (0);
	return (1);
}

int	strlenmap(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i - 1] == ' ')
	{
		i -= 1;
		while (line[i] == ' ')
			i--;
		i++;
	}
	return (i);
}

void	check_fd_error(t_main *main, int fd)
{
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		free(main->map.diff_w);
		free_textures(main);
		exit (ft_printf("Error\nfd not working."));
	}
}

void	empty_line_check(t_main *main, char *line, int fd, int check)
{
	if (check == 0)
	{
		if (line == NULL)
		{
			free_textures(main);
			close(fd);
			exit (ft_printf("Error\nYou entered an empty map !\n"));
		}
		if (line[0] == '\n' || line[0] == '\0')
			main->empty_line = 1;
	}
	if (check == 1)
	{
		if (main->empty_line == 1)
		{
			free_textures(main);
			exit (ft_printf("Error\nYour map has one or more empty lines.\n"));
		}
	}
}
