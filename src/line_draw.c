/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:51:44 by vrudyka           #+#    #+#             */
/*   Updated: 2019/01/17 14:51:46 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		pixel_put(t_img *img, t_var *var, int x, int y)
{
	int			i;


	x += ((var->width * var->s_max )/ 2);
	y += ((var->height * var->s_max )/ 2);
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
	{
		i = (y * WIN_WIDTH) + x;
		((t_color *)img->addr)[i].r = (var->color_1 >> 16) & 0xFF;
		((t_color *)img->addr)[i].g = (var->color_1 >> 8) & 0xFF;
		((t_color *)img->addr)[i].b = (var->color_1) & 0xFF;
		((t_color *)img->addr)[i].a = 0;
	}
}

static int		swapper(int *x0, int *y0, int *x1, int *y1)
{
	int			steep;

	steep = 0;
	if (ABS((*x0) - (*x1)) < ABS((*y0) - (*y1)))
	{
		ft_swap(x0, y0);
		ft_swap(x1, y1);
		steep = 1;
	}
	if ((*x0) > (*x1))
	{
		ft_swap(x0, x1);
		ft_swap(y0, y1);
	}
	return (steep);
}

void			line_draw(t_img *img, t_var *var, t_point zero, t_point one)
{
	int			steep;

	steep = swapper(&(zero.x), &(zero.y), &(one.x), &(one.y));
	(*var).dx = one.x - zero.x;
	(*var).dy = one.y - zero.y;
	(*var).err = ABS((*var).dy) * 2;
	(*var).derr = 0;
	(*var).x = zero.x;
	(*var).y = zero.y;
	while ((*var).x < one.x || (*var).y < one.y)
	{
		if (steep && ((*var).x < WIN_WIDTH || (*var).y < WIN_HEIGHT))
			pixel_put(img, var, (*var).y, (*var).x);
		else if ((*var).x < WIN_WIDTH || (*var).y < WIN_HEIGHT)
			pixel_put(img, var,(*var).x, (*var).y);
		(*var).derr += (*var).err;
		if ((*var).derr > (*var).dx)
			{
				(*var).y += (one.y > zero.y ? 1 : -1);
				(*var).derr -= (*var).dx * 2;
			}
		else if ((*var).x < one.x)
			(*var).x++;
	}
}

void			display(t_var *var)
{
	int			y;
	int			x;
	t_point		**map;

	y = -1;
	if (var->map_r == NULL)
		map = var->map_o;
	else
		map = var->map_r;
	while (++y < var->height)
	{
		x = -1;
		while (++x < var->width)
		{
			if (x + 1 != var->width)
				line_draw((*var).img, var, map[y][x], map[y][x + 1]);
			if (y + 1 != var->height)
				line_draw((*var).img, var, map[y + 1][x], map[y][x]);
		}
	}
	mlx_put_image_to_window((*var).img->mlx_ptr, (*var).img->mlx_win,
			(*var).img->ptr, 0, 0);
}