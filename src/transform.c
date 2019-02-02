/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:01:21 by vrudyka           #+#    #+#             */
/*   Updated: 2019/01/24 16:01:22 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	rotate_axis(t_point map, t_rot **rot)
{
	double		y;
	double		z;
	double		x;

	y = map.y;
	z = map.z;
	if ((*rot)->x != 0.0)
	{
		map.y = (y * cos((*rot)->x)) + (z * sin((*rot)->x));
		map.z = -(y * sin((*rot)->x)) + (z * cos((*rot)->x));
	}
	x = map.x;
	z = map.z;
	if ((*rot)->y != 0.0)
	{
		map.x = (x * cos((*rot)->y)) + (z * sin((*rot)->y));
		map.z = -(x * sin((*rot)->y)) + (z * cos((*rot)->y));
	}
	x = map.x;
	y = map.y;
	if ((*rot)->z != 0.0)
	{
		map.x = (x * cos((*rot)->z)) - (y * sin((*rot)->z));
		map.y = (x * sin((*rot)->z)) + (y * cos((*rot)->z));
	}
	return(map);
}

static void		increment_axis(char axis, t_rot **rot)
{
	if (axis == 'x')
		(*rot)->x += TURN_A;
	if (axis == 'y')
		(*rot)->y += TURN_A;
	if (axis == 'z')
		(*rot)->z += TURN_A;
}

void			rotate(t_var *var, char axis, t_rot **rot)
{
	int			y;
	int			x;
	t_point		**map_o;

	y = -1;
	map_o = var->map_o;
	increment_axis(axis, rot);
	var->map_r = (t_point**)malloc(sizeof(t_point*) * var->height);
	ft_bzero(var->img->addr, WIN_HEIGHT * WIN_WIDTH * 4);
	while (++y < var->height)
	{
		x = -1;
		var->map_r[y] = (t_point*)malloc(sizeof(t_point) * var->width);
		while (++x < var->width)
			var->map_r[y][x] = rotate_axis(map_o[y][x], rot);
	}
	var->flag = 1;
	display(var);
}
