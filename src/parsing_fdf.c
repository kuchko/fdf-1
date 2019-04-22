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

void			set_colors(t_var *var, int minZ, int maxZ)
{
	int			red;
	int			blue;
	int			green;
	double		per;

	int			y;
	int			x;

	var->colorMin = 0x27AEE3;
	var->colorMax = 0xFF66CC;

	y = -1;
	while (++y < var->height)
	{
		x = -1;
		while (++x < var->width)
		{
			per = percent(minZ, maxZ, var->map_r[y][x].z);
			red = get_light((var->colorMin >> 16) & 0xFF, (var->colorMax >> 16) & 0xFF, per);
    		green = get_light((var->colorMin >> 8) & 0xFF, (var->colorMax >> 8) & 0xFF, per);
			blue = get_light(var->colorMin & 0xFF, var->colorMax & 0xFF, per);
			var->map_r[y][x].color = var->map_o[y][x].color = ((red << 16) | (green << 8) | blue);
		}
	}
}

void			parsing_line(t_var *var, char *line)
{
	int			i;
	int			y;
	int			x;
	char		**split;

	int			maxZ = 0;
	int			minZ = 2147483647;

	y = 0;
	i = 0;
	var->map_o = (t_point**)malloc(sizeof(t_point*) * var->height);
	var->map_r = (t_point**)malloc(sizeof(t_point*) * var->height);
	split = ft_strsplit(line, ' ');
	while (y < var->height)
	{
		x = 0;
		var->map_r[y] = (t_point*)malloc(sizeof(t_point) * var->width);
		var->map_o[y] = (t_point*)malloc(sizeof(t_point) * var->width);
		while (x < var->width)
		{
			var->map_r[y][x].x = var->map_o[y][x].x = (x - (var->width) / 2) * var->s_max;
			var->map_r[y][x].y = var->map_o[y][x].y = (y - (var->height) / 2) * var->s_max;
			var->map_r[y][x].z = var->map_o[y][x].z = ft_atoi(split[i]) * 10;

			if (maxZ < var->map_r[y][x].z)
				maxZ = var->map_r[y][x].z;
			if (minZ > var->map_r[y][x].z)
				minZ = var->map_r[y][x].z;
			// if (var->map_r[y][x].z > 0)
			// 	var->map_r[y][x].color = 0xFF66CC;
			// else
			// 	var->map_r[y][x].color = 0x27AEE3;
			x++;
			i++;
		}
		y++;
	}
	set_colors(var, minZ, maxZ);
	i = split_count(split); //REVISE
	free(line);
}
