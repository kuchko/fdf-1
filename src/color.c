/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:08:47 by vrudyka           #+#    #+#             */
/*   Updated: 2019/01/25 15:08:49 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			color_assign(t_var *var, int key)
{
	if (key == MAIN_KEY_R)
		var->color_1 = 0xFF00FF;
	else if (key == MAIN_KEY_B)
		var->color_1 = 0x27AEE3;
	else if (key == MAIN_KEY_G)
		var->color_1 = 0x2E8B57;
	display(var);
}
