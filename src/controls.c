/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:34 by vrudyka           #+#    #+#             */
/*   Updated: 2019/01/24 13:41:35 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				X(void *param) //REDO
{
	(void)param;
	exit(0);
	return (0);
}

int				terminate(int error)
{
	if (error == 70)
		ft_putendl("No such file");
	else if (error == 73)
		ft_putendl("Invalid map");
	else if (error == 85)
		ft_putendl("usage: ./fdf [file_name.fdf]");
	exit(0);
	return (0);
}

int				key_down(int key, void *param)
{
	param = NULL;
	if (key == ESC)
		exit(0);
//	if (key == NUM_PAD_6)
	return (0);
}
