/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:03 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/18 14:50:43 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_grids(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->map.h)
	{
		free(main->map.grid[i]);
		i++;
	}
	free(main->map.grid);
}

void	free_textures(t_main *main)
{
	if (main->tex.no)
		free(main->tex.no);
	if (main->tex.so)
		free(main->tex.so);
	if (main->tex.we)
		free(main->tex.we);
	if (main->tex.ea)
		free(main->tex.ea);
	if (main->tex.d)
		free(main->tex.d);
}

void	free_sprites(t_main *main)
{
	if (main->spr_p.img)
		mlx_destroy_image(main->mlx_p, main->spr_p.img);
	if (main->spr_wall.img)
		mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	if (main->spr_floor.img)
		mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	if (main->tex.tex_north.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_north.img);
	if (main->tex.tex_south.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_south.img);
	if (main->tex.tex_west.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_west.img);
	if (main->tex.tex_east.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_east.img);
	if (main->tex.tex_door.img)
		mlx_destroy_image(main->mlx_p, main->tex.tex_door.img);
	mlx_destroy_image(main->mlx_p, main->img);
	mlx_destroy_window(main->mlx_p, main->mlx_win);
	mlx_destroy_display(main->mlx_p);
	free(main->mlx_p);
	free_grids(main);
	free(main->map.diff_w);
	free_textures(main);
}

void	free_diff_tex_grids(t_main *main, int check)
{
	free(main->map.diff_w);
	free_textures(main);
	free_grids(main);
	if (check == 1)
		exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
}
