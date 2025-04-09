/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:38:49 by zamgar            #+#    #+#             */
/*   Updated: 2025/04/09 13:54:15 by zamgar           ###   ########.fr       */
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

int	get_rgb(char *line, int rgb)
{
	int	i;
	int	j;
	int	r;
	int	g;
	int	b;
	int	c;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	c = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] < 58 && line[i] > 47)
		{
			j = 0;
			while (line[i + j] && j < 3 && (line[i + j] < 58 && line[i + j] > 47))
			{
				if (c == 0)
				{
					r *= 10;
					r += line[i + j] - 48;
				}
				if (c == 1)
				{
					g *= 10;
					g += line[i + j] - 48;
				}
				if (c == 2)
				{
					b *= 10;
					b += line[i + j] - 48;
				}
				j++;
			}
			c++;
			i+=j;
		}
		i++;
	}
	if (rgb == 1)
		return (r);
	if (rgb == 2)
		return (g);
	return (b);
}

int	rgbToHex(char *line)
{
    char	res[7] = "0000000";
	int		dec;

	dec = 0;
	int r = get_rgb(line, 1);
	int g = get_rgb(line, 2);
	int b = get_rgb(line, 3);
    int r0 = r/16;
    int g0 = g/16;
    int b0 = b/16;
    res[0] = HEXA[r0];
    res[1] = HEXA[r - (16 * r0)];
    res[2] = HEXA[g0];
    res[3] = HEXA[g - (16 * g0)];
    res[4] = HEXA[b0];
    res[5] = HEXA[b - (16 * b0)];
    res[6] = '\0';
	dec = get_index_hex(res[5]) + get_index_hex(res[4]) * 16
		+ get_index_hex(res[3]) * pow(16, 2) + get_index_hex(res[2]) * pow(16, 3)
		+ get_index_hex(res[1]) * pow(16, 4) + get_index_hex(res[0]) * pow(16, 5);
	return (dec);
}
