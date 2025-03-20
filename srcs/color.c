#include "../includes/cub3d.h"

int get_index_hex(char c)
{
	int i = 0;
	char hex[] = "0123456789ABCDEF";
	while (i < 16)
	{
		if (hex[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_rgb(char *line, int rgb)
{
	int i = 0;
	int j;
	int r = 0;
	int g = 0;
	int b = 0;
	int c = 0;
	while (line[i] && line[i] != '\n')
	{
		if (ft_isdigit(line[i]))
		{
			j = 0;
			while (line[i + j] && j < 3 && ft_isdigit(line[i + j]))
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

int	check_tmp(char *tmp)
{
	if ((int)ft_atoi(tmp) < 0 || (int)ft_atoi(tmp) > 255)
		return (free(tmp), 0);
	return (free(tmp), 1);
}

int	check_line_rgb(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '+' || line[i] == '-' || ft_isdigit(line[i]))
		{
			if (line[i] == '-' || line[i] == '+')
				j = i + 1;
			else
				j = i;
			while(line[j] && line[j] != '\n' && ft_isdigit(line[j]))
				j++;
			tmp = ft_substr(line, i, j - i);
		}
		if (!check_tmp(tmp))
			return (0);
		i += (j - i + 1);
	}

	return (1);
}

int    rgbToHex(char *line)
{
    char hex[] = "0123456789ABCDEF";
    char res[7] = "0000000";
	int dec = 0;

	if (!check_line_rgb(line))
	{
		printf("RGB ERROR\n");
		return (-1);
	}
	int r = get_rgb(line, 1);
	int g = get_rgb(line, 2);
	int b = get_rgb(line, 3);
    int r0 = r/16;
    int g0 = g/16;
    int b0 = b/16;
    res[0] = hex[r0];
    res[1] = hex[r - (16 * r0)];
    res[2] = hex[g0];
    res[3] = hex[g - (16 * g0)];
    res[4] = hex[b0];
    res[5] = hex[b - (16 * b0)];
    res[6] = '\0';
	dec = get_index_hex(res[5]) + get_index_hex(res[4]) * 16
		+ get_index_hex(res[3]) * pow(16, 2) + get_index_hex(res[2]) * pow(16, 3)
		+ get_index_hex(res[1]) * pow(16, 4) + get_index_hex(res[0]) * pow(16, 5);
		return (dec);
}
