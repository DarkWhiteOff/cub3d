/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeezou <zeezou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:31 by zamgar            #+#    #+#             */
/*   Updated: 2025/04/12 08:24:31 by zeezou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void get_params(t_main *main, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		main->tex.NO = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "SO ", 3) == 0)
		main->tex.SO = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "WE ", 3) == 0)
		main->tex.WE = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "EA ", 3) == 0)
		main->tex.EA = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "D ", 2) == 0)
		main->tex.D = ft_substr(line, 2, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "C", 1) && main->tex.color_c == -1)
		main->tex.color_c = rgbToHex(line);
	if (!ft_strncmp(line, "F", 1) && main->tex.color_f == -1)
		main->tex.color_f = rgbToHex(line);
}

void get_map_start(t_main *main)
{
	char	*line;
	int		check;

	check = 0;
	line = get_next_line(main->fd);
	while (line)
	{
		if (line[0] == '\n' && check == 0)
			main->tex.map_start++;
		else
			check = 1;
		free(line);
		line = get_next_line(main->fd);
	}
}

void	get_infos(t_main *main)
{
	char	*line;

	main->fd = open(main->map.path, O_RDONLY);
	if (main->fd < 0 || read(main->fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
	line = get_next_line(main->fd);
	while (line)
	{
		main->tex.map_start++;
		get_params(main, line);
		free(line);
		if (main->tex.NO && main->tex.SO && main->tex.WE && main->tex.EA
			&& main->tex.D && main->tex.color_c != -1 && main->tex.color_f != -1)
			break ;
		line = get_next_line(main->fd);
	}
	if (!main->tex.NO || !main->tex.SO || !main->tex.WE || !main->tex.EA
		|| !main->tex.D || main->tex.color_c == -1 || main->tex.color_f == -1)
	{
		free_textures(main);
		exit(ft_printf("Error\nTextures missing.\n"));
	}
	get_map_start(main);
}

void	get_diff_width(t_main *main)
{
	char	*l;
	int		map_start;
	int		i;

	i = 0;
	main->map.diff_w = (int *)malloc(sizeof(int) * (main->map.h + 1));
	map_start = main->tex.map_start;
	main->fd2 = open(main->map.path, O_RDONLY);
	check_fd_error(main, main->fd2);
	l = get_next_line(main->fd2);
	while (map_start--)
	{
		free(l);
		l = get_next_line(main->fd2);
	}
	while (l)
	{
		main->map.diff_w[i++] = strlenmap(l);
		free(l);
		l = get_next_line(main->fd2);
	}
	close(main->fd2);
	main->map.diff_w[i] = -1;
}

int	check_w(int *array)
{
	int	i;

	i = 0;
	while (array[i] != -1)
	{
		if (array[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void check_w_h(t_main *main)
{
	if (check_w(main->map.diff_w) == 0 || main->map.h == 0)
	{
		free(main->map.diff_w);
		free_textures(main);
		exit (ft_printf("Error\nMap not rectangular / nothing in it.\n"));
	}
}

void	parse_map(t_main *main)
{
	char	*l;
	int		map_start;

	map_start = main->tex.map_start;
	main->fd1 = open(main->map.path, O_RDONLY);
	check_fd_error(main, main->fd1);
	l = get_next_line(main->fd1);
	while (map_start--)
	{
		free(l);
		l = get_next_line(main->fd1);
	}
	while (l)
	{
		main->map.h++;
		empty_line_check(main, l, main->fd1);
		free(l);
		l = get_next_line(main->fd1);
	}
	close(main->fd1);
	get_diff_width(main);
	check_w_h(main);
}
