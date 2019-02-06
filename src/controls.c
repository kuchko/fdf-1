/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:34 by vrudyka           #+#    #+#             */
/*   Updated: 2019/02/06 15:52:57 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				termin(void *param)
{
	(void)param;
	exit(0);
}

int				terminate(char *str)
{
	ft_putendl(str);
	exit(0);
}

void			color_assign(t_var *var, int key)
{
	if (key == MAIN_KEY_R)
		var->color = 0xFF00FF;
	else if (key == MAIN_KEY_B)
		var->color = 0x27AEE3;
	else if (key == MAIN_KEY_G)
		var->color = 0x2E8B57;
	display(var);
}

int				key_down(int key, t_var *var)
{
	static t_rot	*rot;

	if (rot == NULL)
	{
		rot = malloc(sizeof(t_rot));
		rot->x = 0.0;
		rot->y = 0.0;
		rot->z = 0.0;
	}
	if (key == ESC)
		exit(0);
	else if (key == ARROW_UP)
		rotate(var, 'x', &rot);
	else if (key == ARROW_L)
		rotate(var, 'y', &rot);
	else if (key == ARROW_R)
		rotate(var, 'z', &rot);
	else if (key == MAIN_KEY_I)
		iso(var);
	else if (key == MAIN_KEY_R || key + MAIN_KEY_B)
		color_assign(var, key);
	return (0);
}
