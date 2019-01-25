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

static void		axis_x(t_point *map)
{
	int			y;
	int			z;

	y = map->y;
	z = map->z;
	map->y = (y * cos(0.2)) + (z * sin(0.2));
	map->z = -(y * sin(0.2)) + (z * cos(0.2));
}

static void		axis_y(t_point *map)
{
	int			x;
	int			z;

	x = map->x;
	z = map->z;
	map->x = (x * cos(0.2)) + (z * sin(0.2));
	map->z = -(x * sin(0.2)) + (z * cos(0.2));
}

static void		axis_z(t_point *map)
{
	int			x;
	int			y;

	x = map->x;
	y = map->y;
	map->x = (x * cos(0.2)) - (y * sin(0.2));
	map->y = (x * sin(0.2)) + (y * cos(0.2));
}

void			rotate(t_var *var, char axis)
{
	int			y;
	int			x;
	t_point		**map;

	y = -1;
	map = var->map;
	ft_bzero(var->img->addr, WIN_HEIGHT * WIN_WIDTH * 4);
	while (++y < var->height)
	{
		x = -1;
		while (++x < var->width)
		{
			if (axis == 'x')
				axis_x(&map[y][x]);
			else if (axis == 'y')
				axis_y(&map[y][x]);
			else if (axis == 'z')
				axis_z(&map[y][x]);
		}
	}
	display(var);
}
