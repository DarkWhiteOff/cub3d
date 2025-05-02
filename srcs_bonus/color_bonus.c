/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:49 by zamgar            #+#    #+#             */
/*   Updated: 2025/05/01 13:52:36 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	get_index_hex(char c)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (HEXA[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_red(char *line)
{
	int	i;
	int	j;
	int	r;

	i = 0;
	j = 0;
	r = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] < 58 && line[i] > 47)
		{
			j = 0;
			while (line[i + j] && j < 3
				&& (line[i + j] < 58 && line[i + j] > 47))
			{
				r *= 10;
				r += line[i + j] - 48;
				j++;
			}
			break ;
		}
		i++;
	}
	return (r);
}

int	get_green(char *line)
{
	int	i;
	int	j;
	int	g;

	i = 0;
	j = 0;
	g = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] < 58 && line[i] > 47 && j == 1)
		{
			while (line[i + j - 1] && j - 1 < 3
				&& (line[i + j - 1] < 58 && line[i + j - 1] > 47))
			{
				g *= 10;
				g += line[i + j - 1] - 48;
				j++;
			}
			break ;
		}
		else if (line[i] == ',')
			j++;
		i++;
	}
	return (g);
}

int	get_blue(char *line)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	j = 0;
	b = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] < 58 && line[i] > 47 && j == 2)
		{
			while (line[i + j - 2] && j - 2 < 3
				&& (line[i + j - 2] < 58 && line[i + j - 2] > 47))
			{
				b *= 10;
				b += line[i + j - 2] - 48;
				j++;
			}
			break ;
		}
		else if (line[i] == ',')
			j++;
		i++;
	}
	return (b);
}

int	rgb_to_hex(char *line)
{
	char		res[7];
	int			dec;
	int			r0;
	int			g0;
	int			b0;

	dec = 0;
	r0 = get_red(line) / 16;
	g0 = get_green(line) / 16;
	b0 = get_blue(line) / 16;
	res[0] = HEXA[r0];
	res[1] = HEXA[get_red(line) - (16 * r0)];
	res[2] = HEXA[g0];
	res[3] = HEXA[get_green(line) - (16 * g0)];
	res[4] = HEXA[b0];
	res[5] = HEXA[get_blue(line) - (16 * b0)];
	res[6] = '\0';
	dec = get_index_hex(res[5]) + get_index_hex(res[4]) * 16
		+ get_index_hex(res[3]) * pow(16, 2)
		+ get_index_hex(res[2]) * pow(16, 3)
		+ get_index_hex(res[1]) * pow(16, 4)
		+ get_index_hex(res[0]) * pow(16, 5);
	return (dec);
}
