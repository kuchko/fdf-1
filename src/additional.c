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
