/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:47:16 by zamgar            #+#    #+#             */
/*   Updated: 2025/06/04 13:25:22 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ss;
	char	*dest;

	i = 0;
	ss = (char *)s;
	while (ss[i] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (ss[i] != '\0')
	{
		dest[i] = ss[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*ss;

	i = 0;
	cc = (char)c;
	ss = (char *)s;
	while (ss[i] != '\0')
	{
		if (s[i] == cc)
			return (&ss[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*newstr;

	i = ft_strlen(s1) + ft_strlen(s2);
	j = 0;
	newstr = (char *)malloc(sizeof(char) * i + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i] = s2[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

unsigned char	*unsigned_ft_strjoin(unsigned char const *s1,
					unsigned char const *s2)
{
	size_t			i;
	size_t			j;
	unsigned char	*newstr;

	i = unsigned_ft_strlen(s1) + unsigned_ft_strlen(s2);
	j = 0;
	newstr = (unsigned char *)malloc(sizeof(unsigned char) * i + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i] = s2[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t		i;
	char		*newstr;

	i = 0;
	if (!str)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	while (i < len)
	{
		newstr[i] = str[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
