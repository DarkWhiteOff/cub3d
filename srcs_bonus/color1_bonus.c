/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:02:18 by tzizi             #+#    #+#             */
/*   Updated: 2025/06/24 17:11:50 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	check_line_rgb2(char *line, int *i, int *nb)
{
	char	*tmp;
	int		j;

	j = *i;
	while (line[j] && line[j] < 58 && line[j] > 47
		|| line[j] == '-' || line[j] == '+')
		j++;
	if (j - *i > 0)
	{
		tmp = ft_substr(line, *i, j - *i);
		if (ft_atoi(tmp) < 0 || ft_atoi(tmp) > 255)
			return (free(tmp), 0);
		else
			(*nb)++;
		free(tmp);
		(*i) = j;
	}
	else
		(*i)++;
	return (1);
}

int	check_line_rgb(char *line)
{
	int		i;
	int		comma;
	int		nb;

	i = 0;
	comma = 0;
	nb = 0;
	while (line[i] == ' ' && line[i])
		i++;
	if (line[i] != 'C' && line[i] != 'F')
		return (0);
	i++;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == ',')
			comma++;
		if (check_line_rgb2(line, &i, &nb) == 0)
			return (0);
	}
	return (1 && comma == 2 && nb == 3);
}

void	grid_init1(t_main *main, char **line)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (i < main->map.h)
	{
		if (main->malloc_fail != 1)
		{
			while (j < main->map.diff_w[i])
				main->map.grid[i][j++] = (*line)[j];
			while (j < main->map.w_max)
				main->map.grid[i][j++] = ' ';
			main->map.grid[i++][j] = '\0';
			j = 0;
		}
		else
			i++;
		free(*line);
		(*line) = get_next_line(main->fd3);
	}
}
