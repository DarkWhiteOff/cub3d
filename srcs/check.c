#include "../includes/cub3d.h"

void	get_infos(t_main *main)
{
	char	*line;
	int NO = 0;
	int SO = 0;
	int WE = 0;
	int EA = 0;

	main->fdtest = open(main->map.path, O_RDONLY);
	if (main->fdtest < 0 || read(main->fdtest, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
	line = get_next_line(main->fdtest);
	while (line)
	{
		main->tex.map_start++;
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			main->tex.NO = ft_substr(line, 3, ft_strlen(line) - 3);
			NO = 1;
		}
		if (ft_strncmp(line, "SO ", 3) == 0)
		{
			main->tex.SO = ft_substr(line, 3, ft_strlen(line) - 3);
			SO = 1;
		}
		if (ft_strncmp(line, "WE ", 3) == 0)
		{
			main->tex.WE = ft_substr(line, 3, ft_strlen(line) - 3);
			WE = 1;
		}
		if (ft_strncmp(line, "EA ", 3) == 0)
			{
			main->tex.EA = ft_substr(line, 3, ft_strlen(line) - 3);
			EA = 1;
		}
		if (!ft_strncmp(line, "C", 1) && main->tex.color_c == -1)
			main->tex.color_c = rgbToHex(line);
		if (!ft_strncmp(line, "F", 1) && main->tex.color_f == -1)
			main->tex.color_f = rgbToHex(line);
		free(line);
		if (NO == 1 && SO == 1 && WE == 1 && EA == 1
			&& main->tex.color_c != -1 && main->tex.color_f != -1)
			break ;
		// printf("iic : %d\n", main->tex.color_c);
		// printf("iic : %d\n", main->tex.color_f);
		line = get_next_line(main->fdtest);
	}
	if (NO != 1 && SO != 1 && WE != 1 && EA != 1 && main->tex.color_c == -1 && main->tex.color_f == -1)
	{
		free_textures(main);
		exit(ft_printf("Error\nTextures missing.\n"));
	}
	int check = 0;
	line = get_next_line(main->fdtest);
	while (line)
	{
		if (line[0] == '\n' && check == 0)
			main->tex.map_start++;
		else
			check = 1;
		free(line);
		line = get_next_line(main->fdtest);
	}
}

void get_diff_width(t_main *main)
{
	int map_start = main->tex.map_start;
	char	*l;
	int i = 0;

	main->fdtest2 = open(main->map.path, O_RDONLY);
	check_fd_error(main, main->fdtest2);
	l = get_next_line(main->fdtest2);
	while (map_start--)
	{
		free(l);
		l = get_next_line(main->fdtest2);
	}
	while (l)
	{
		main->map.diff_w[i++] = strlenmap(l);
		free(l);
		l = get_next_line(main->fdtest2);
	}
	close(main->fdtest2);
	main->map.diff_w[i] = -1;
}

int	check_w(int *array)
{
	int i = 0;
	while (array[i] != -1)
	{
		if (array[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(t_main *main)
{
	char	*l;
	int map_start = main->tex.map_start;

	main->fdtest1 = open(main->map.path, O_RDONLY);
	check_fd_error(main, main->fdtest1);
	l = get_next_line(main->fdtest1);
	while (map_start--)
	{
		free(l);
		l = get_next_line(main->fdtest1);
	}
	while (l)
	{
		main->map.h++;
		empty_line_check(main, l, main->fdtest1);
		free(l);
		l = get_next_line(main->fdtest1);
	}
	close(main->fdtest1);
	main->map.diff_w = (int *)malloc(sizeof(int) * (main->map.h + 1));
	get_diff_width(main);
	if (check_w(main->map.diff_w) == 0 || main->map.h == 0)
	{
		free(main->map.diff_w);
		free_textures(main);
		exit (ft_printf("Error\nMap not rectangular / nothing in it.\n"));
	}
}
