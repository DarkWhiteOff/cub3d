/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:15 by zamgar            #+#    #+#             */
/*   Updated: 2025/05/01 11:48:06 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	get_img_addr(t_main *main)
{
	main->tex.tex_north.addr = mlx_get_data_addr(main->tex.tex_north.img,
		&main->tex.tex_north.b, &main->tex.tex_north.ls,
		&main->tex.tex_north.end);
	main->tex.tex_south.addr = mlx_get_data_addr(main->tex.tex_south.img,
		&main->tex.tex_south.b, &main->tex.tex_south.ls,
		&main->tex.tex_south.end);
	main->tex.tex_west.addr = mlx_get_data_addr(main->tex.tex_west.img,
		&main->tex.tex_west.b, &main->tex.tex_west.ls, 
		&main->tex.tex_west.end);
	main->tex.tex_east.addr = mlx_get_data_addr(main->tex.tex_east.img,
		&main->tex.tex_east.b, &main->tex.tex_east.ls,
		&main->tex.tex_east.end);
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
