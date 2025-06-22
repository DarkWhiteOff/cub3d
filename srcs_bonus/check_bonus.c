/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeezou <zeezou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:31 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/23 00:40:06 by zeezou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_double(t_main *main, char *line, int check)
{
	if (check == 0)
	{
		if (ft_strncmp(line, "NO ", 3) == 0 && main->tex.no)
			main->double_tex = 1;
		if (ft_strncmp(line, "SO ", 3) == 0 && main->tex.so)
			main->double_tex = 1;
		if (ft_strncmp(line, "WE ", 3) == 0 && main->tex.we)
			main->double_tex = 1;
		if (ft_strncmp(line, "EA ", 3) == 0 && main->tex.ea)
			main->double_tex = 1;
		if (ft_strncmp(line, "DO ", 2) == 0 && main->tex.d)
			main->double_tex = 1;
		if (!ft_strncmp(line, "C ", 2) && main->tex.color_c != -1)
			main->double_tex = 1;
		if (!ft_strncmp(line, "F ", 2) && main->tex.color_f != -1)
			main->double_tex = 1;
		printf("main->double_tex : %d\n", main->double_tex);
	}
	if (check == 1 && main->double_tex == 1)
	{
		close(main->fd);
		free_textures(main);
		exit(printf("Error\nDouble texture.\n"));
	}
}

void	get_params(t_main *main, char *line)
{
	int	i;

	i = 2;
	check_double(main, line, 0);
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(line, "NO ", 3) == 0 && main->double_tex == 0)
		main->tex.no = ft_substr(line, i, ft_strlen(line) - (i + 1));
	if (ft_strncmp(line, "SO ", 3) == 0 && main->double_tex == 0)
		main->tex.so = ft_substr(line, i, ft_strlen(line) - (i + 1));
	if (ft_strncmp(line, "WE ", 3) == 0 && main->double_tex == 0)
		main->tex.we = ft_substr(line, i, ft_strlen(line) - (i + 1));
	if (ft_strncmp(line, "EA ", 3) == 0 && main->double_tex == 0)
		main->tex.ea = ft_substr(line, i, ft_strlen(line) - (i + 1));
	if (ft_strncmp(line, "DO ", 2) == 0 && main->double_tex == 0)
		main->tex.d = ft_substr(line, i, ft_strlen(line) - (i + 1));
	if (!ft_strncmp(line, "C ", 2) && main->tex.color_c == -1)
		main->tex.color_c = rgb_to_hex(line);
	if (!ft_strncmp(line, "F ", 2) && main->tex.color_f == -1)
		main->tex.color_f = rgb_to_hex(line);
}

void	get_map_start(t_main *main)
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
	close(main->fd);
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
		if (main->tex.no && main->tex.so && main->tex.we && main->tex.ea
			&& main->tex.color_c != -1 && main->tex.color_f != -1
			&& main->tex.d)
			break ;
		line = get_next_line(main->fd);
	}
	get_map_start(main);
	check_double(main, line, 1);
	if (!main->tex.no || !main->tex.so || !main->tex.we || !main->tex.ea
		|| main->tex.color_c == -1 || main->tex.color_f == -1 || !main->tex.d)
	{
		free_textures(main);
		close(main->fd);
		exit(ft_printf("Error\nTextures missing.\n"));
	}
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
		if (strlenmap(l) > main->map.w_max)
			main->map.w_max = strlenmap(l);
		free(l);
		l = get_next_line(main->fd2);
	}
	close(main->fd2);
	main->map.diff_w[i] = -1;
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
		empty_line_check(main, l, main->fd1, 0);
		free(l);
		l = get_next_line(main->fd1);
	}
	close(main->fd1);
	empty_line_check(main, l, main->fd1, 1);
	get_diff_width(main);
	check_w_h(main);
}
