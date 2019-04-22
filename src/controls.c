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

static void		key_num(int key, t_var *var, t_rot **rot)
{
	if (key == NUM_2)
		rotate(var, 'x', rot);
	else if (key == NUM_6)
		rotate(var, 'y', rot);
	else if (key == NUM_9)
		rotate(var, 'z', rot);
	else if (key == NUM_8)
		rotate(var, 'c', rot);
	else if (key == NUM_4)
		rotate(var, 'u', rot);
	else if (key == NUM_7)
		rotate(var, 'a', rot);
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
	else if (key == NUM_2 || key == NUM_4 || key == NUM_6 ||
			key == NUM_7 || key == NUM_8 || key == NUM_9)
		key_num(key, var, &rot);
	else if (key == MAIN_KEY_I)
		iso(var);
	else if (key == MAIN_KEY_R || key == MAIN_KEY_B)
		color_assign(var, key);
	update(var);
	return (0);
}

void			color_assign(t_var *var, int key)
{
	if (key == MAIN_KEY_R)
		var->color = 0xFF00FF;
	else if (key == MAIN_KEY_B)
		var->color = 0x27AEE3;
	else if (key == MAIN_KEY_G)
		var->color = 0x2E8B57;
	update(var);
}

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
