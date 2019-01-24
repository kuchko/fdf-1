/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:35:23 by vrudyka           #+#    #+#             */
/*   Updated: 2019/01/17 13:35:24 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		width_count(char *line)
{
	int			i;
	char		**split;

	i = 0;
	split = ft_strsplit(line, ' ');
	while (split[i])
		i++;
	free(split);
	return (i);
}

static char		*ft_strjoin_free(char *line, char *buf, int width)
{
	char		*point;

	point = line;
	if (width_count(buf) != width)
		terminate(73);
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, buf);
	free(point);
	free(buf);
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
	}
	(*var)->width = width;
	(*var)->height = height;
	if ((*var)->height < (*var)->width)
		(*var)->s_max = WIN_HEIGHT / ((*var)->height + 4);
	else
		(*var)->s_max = WIN_WIDTH / ((*var)->width + 4);
	return (line);
}

t_point			**parsing_line(t_var *var, char *line)
{
	int			y;
	int			x;
	char		**split;
	t_point		**map;

	y = -1;
	map = (t_point**)malloc(sizeof(t_point*) * var->height);
	split = ft_strsplit(line, ' ');
	while (++y < var->height)
	{
		x = -1;
		map[y] = (t_point*)malloc(sizeof(t_point) * var->width);
		while (++x < var->width)
		{
			map[y][x].x = (x * var->s_max) - ((var->width * var->s_max )/ 2);
			map[y][x].y = (y * var->s_max) - ((var->height * var->s_max )/ 2);
			map[y][x].z = ft_atoi(*split) * var->s_max;
			//printf("x: %d y: %d z: %d\n", map[y][x].x, map[y][x].y, map[y][x].z);
			split++;
		}
	}
	return (map);
}
