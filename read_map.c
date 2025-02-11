/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:51:27 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/11 19:20:29 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	if_passed_textures(char	*line)
{
	static int	count;

	if (ft_strncmp(line, "NO", 2) == 0)
		count++;
	else if (ft_strncmp(line, "SO", 2) == 0)
		count++;
	else if (ft_strncmp(line, "EA", 2) == 0)
		count++;
	else if (ft_strncmp(line, "WE", 2) == 0)
		count++;
	else if (ft_strncmp(line, "F", 1) == 0)
		count++;
	else if (ft_strncmp(line, "C", 1) == 0)
		count++;
	return (count);
}
static void	double_new_line(char *line)
{
	int	i;
	static int	flag;

	i = 0;
	flag = 0;
	if (!line)
		return ;
	while (line[i] && line[i + 1])
	{
		if (if_passed_textures(line + i) == 6 && flag == 0)
		{
			while (line[i] && line[i] != '\n')
				i++;
			while (line[i] && line[i] == '\n')
				i++;
			flag = 1;
		}
		if (line[i] == '\n' && line[i + 1] == '\n' && flag == 1)
			error("Validation failed!\n", line);
		if (line[i] != '\0')
		i++;
	}
}

static char	*check_line(char **new_line, char **line)
{
	*new_line = another_strtrim((*line), "\n");
	if (!(*new_line))
		free_line((*new_line), (*line));
	double_new_line((*new_line));
	return ((*new_line));
}

static char	*get_the_line(int fd)
{
	char	*tmp;
	char	*line;
	char	*check;

	tmp = NULL;
	line = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		check = ft_strtrim(tmp, " \n\t\v");
		if (!check)
		{
			free_line(tmp, check);
			error("Validation failed!\n", line);
		}
		line = ft_strjoin(line, check);
		free_line(tmp, check);
		if (!line)
			error("Validation failed!\n", line);
	}
	free_line(tmp, NULL);
	return (line);
}

char	**read_map(int fd)
{
	char	*line;
	char	*new;
	char	**map;

	line = NULL;
	new = NULL;
	map = NULL;
	line = get_the_line(fd);
	if (!line || line_is_empty(line))
		error ("Validation failed!\n", line);
	new = check_line(&new, &line);
	if (!new)
		free_line(line, new);
	free_line(line, NULL);
	map = split(new, '\n');
	if (!map)
	{
		free_line(line, new);
		clean(NULL, map, "Validation failed!\n");
	}
	free_line(new, NULL);
	return (map);
}
