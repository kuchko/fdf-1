/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:23:13 by vrudyka           #+#    #+#             */
/*   Updated: 2019/02/06 17:23:15 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point			**map_memalloc(t_var *var)
{
	int			y;
	t_point		**map;

	y = 0;
	map = (t_point**)malloc(sizeof(t_point*) * var->height);
	while (y < var->height)
	{
		map[y] = (t_point*)malloc(sizeof(t_point) * var->width);
		y++;
	}
	return (map);
}

void			s_max(t_var *var)
{
	if (var->height < var->width)
		var->s_max = WIN_HEIGHT / (var->height + 4);
	else
		var->s_max = WIN_WIDTH / (var->width + 4);
	if (var->s_max > 48)
		var->s_max = 48;
}

void			free_map(t_point **map, t_var *var)
{
	int			y;

	y = -1;
	while (++y < var->height)
	{
		free(map[y]);
	}
	free(map);
}
