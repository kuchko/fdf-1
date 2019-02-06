/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:35:23 by vrudyka           #+#    #+#             */
/*   Updated: 2019/02/06 15:53:12 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		width_count(char *line)
{
	int			i;
	char		**split;

	split = ft_strsplit(line, ' ');
	i = split_count(split);
	return (i);
}

static char		*ft_strjoin_free(char *line, char *buf, int width)
{
	char		*point;

	point = line;
	if (width_count(buf) != width)
		terminate("Invalid map");
	line = ft_strjoin(line, " ");
	free(point);
	point = line;
	line = ft_strjoin(line, buf);
	free(point);
	return (line);
}

char			*parsing_fdf(int fd, t_var **var)
{
	int			width;
	int			height;
	char		*buf;
	char		*line;

	height = 0;
	while (get_next_line(fd, &buf))
	{
		if (height == 0)
		{
			line = ft_strdup(buf);
			width = width_count(buf);
		}
		else
			line = ft_strjoin_free(line, buf, width);
		height++;
		free(buf);
	}
	(*var)->width = width;
	(*var)->height = height;
	s_max((*var));
	return (line);
}

t_point			**parsing_line(t_var *var, char *line)
{
	int			y;
	int			x;
	char		**split;
	t_point		**map;

	y = -1;
	(*var).i = 0;
	map = (t_point**)malloc(sizeof(t_point*) * var->height);
	split = ft_strsplit(line, ' ');
	while (++y < var->height)
	{
		x = -1;
		map[y] = (t_point*)malloc(sizeof(t_point) * var->width);
		while (++x < var->width)
		{
			map[y][x].x = (x - (var->width) / 2) * var->s_max;
			map[y][x].y = (y - (var->height) / 2) * var->s_max;
			map[y][x].z = ft_atoi(split[(*var).i]) * 10;
			(*var).i++;
		}
	}
	(*var).i = split_count(split);
	free(line);
	return (map);
}
