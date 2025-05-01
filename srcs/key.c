/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:39:11 by zamgar            #+#    #+#             */
/*   Updated: 2025/05/01 13:51:40 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_manager_down(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == 65307)
		close_window(main);
	if (keycode == 119)
		main->map.z = 1;
	if (keycode == 97)
		main->map.q = 1;
	if (keycode == 115)
		main->map.s = 1;
	if (keycode == 100)
		main->map.d = 1;
	if (keycode == 65361)
		main->map.left = 1;
	if (keycode == 65363)
		main->map.right = 1;
	return (0);
}

int	key_manager_up(int keycode, t_main *main)
{
	if (keycode == 119)
		main->map.z = 0;
	if (keycode == 97)
		main->map.q = 0;
	if (keycode == 115)
		main->map.s = 0;
	if (keycode == 100)
		main->map.d = 0;
	if (keycode == 65361)
		main->map.left = 0;
	if (keycode == 65363)
		main->map.right = 0;
	return (0);
}
