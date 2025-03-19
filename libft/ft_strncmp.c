/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:54 by zamgar            #+#    #+#             */
/*   Updated: 2024/05/31 14:55:31 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
//#include <stdio.h>
//#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*ss1;
	char	*ss2;

	i = 0;
	ss1 = (char *)s1;
	ss2 = (char *)s2;
	if (n == 0)
		return (0);
	n = n - 1;
	while (ss1[i] == ss2[i] && ss1[i] != '\0' && ss2[i] != '\0' && i < n)
		i++;
	return ((unsigned char)ss1[i] - (unsigned char)ss2[i]);
}

/*int     main()
{
        //const char s1[20] = "abcdefgh";
        //const char s2[20] = "abcdwxyz";
	printf("%d\n", ft_strncmp("abcdefgh", "abcdwxyz", 4));
        printf("%d\n", ft_strncmp("zyxbcdefgh", "abcdwxyz", 0));
	printf("%d\n", ft_strncmp("abcdefgh", "", 0));
	printf("%d\n", ft_strncmp("test\200", "test\0", 6));

	printf("%d\n", strncmp("abcdefgh", "abcdwxyz", 4));
        printf("%d\n", strncmp("zyxbcdefgh", "abcdwxyz", 0));
        printf("%d\n", strncmp("abcdefgh", "", 0));
        printf("%d\n", strncmp("test\200", "test\0", 6));
	return (0);
}*/
