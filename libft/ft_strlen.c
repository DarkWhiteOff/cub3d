/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:26:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/03/20 16:20:50 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	unsigned_ft_strlen(unsigned const char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
		i++;
	return (i);
}