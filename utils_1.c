/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:57:51 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/10 15:03:52 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
char	*substr_alter(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
	{
		return (NULL);
	}
	while (i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[len] = '\n';
	str[len + 1] = '\0';
	return (str);
}
int	height(char **map)
{
	int	i;

	i = 0;
	if (!map || !(*map))
		return (0);
	while (map[i])
		i++;
	return (i);
}

int	width(char **map)
{
	int	i;

	i = 0;
	if (!map || !map[0][i])
		return (0);
	while (map[0][i])
		i++;
	return (i);
}
int max_column(char **map)
{
    int i = 0;
    int max_length = 0;
	int j = 0;
	int tab = 0;


    while (map[i] != NULL)
    {
		j = 0;
        while (map[i][j] != '\0')
        {
			if (map[i][j] == '\t')
				tab += 3;
            j++;
        }
        if (j + tab > max_length)
        {
            max_length = j + tab;
        }

        i++;
    }
    return max_length;
}
