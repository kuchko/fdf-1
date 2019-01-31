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
		((t_color *)img->addr)[i].r = (var->color >> 16) & 0xFF;
		((t_color *)img->addr)[i].g = (var->color >> 8) & 0xFF;
		((t_color *)img->addr)[i].b = (var->color) & 0xFF;
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

static void		line_draw(t_img *img, t_var *var, t_point zero, t_point one)
{
	int			steep;

	steep = swapper(&(zero.x), &(zero.y), &(one.x), &(one.y));
	(*var).x = zero.x;
	(*var).y = zero.y;
	(*var).dx = one.x - zero.x;
	(*var).dy = one.y - zero.y;
	(*var).err = ABS(2 * (*var).dy);
	(*var).derr = 0;
	(*var).sy = (one.y > zero.y ? 1 : -1);
	//printf("dx: %d, dy: %d, err: %d\n", (*var).dx, (*var).dy, (*var).err);
	while (zero.x < one.x || zero.y < one.y)
	{
		if (steep && zero.x < WIN_WIDTH && zero.y < WIN_HEIGHT)
			pixel_put(img, var, zero.y, zero.x);
		else if (zero.x < WIN_WIDTH && zero.y < WIN_HEIGHT)
			pixel_put(img, var, zero.x, zero.y);
		(*var).derr += (*var).err;
		if ((*var).derr > (*var).dx)
			{
				zero.y += (*var).sy;
				(*var).derr -= (*var).dx * 2;
			}
		if (zero.x < one.x)
			zero.x++;
	}
}

void			display(t_var *var)
{
	int			y;
	int			x;
	t_point		**map;

	y = 0;
	if (var->flag == 0)
		map = var->map_o;
	else
		map = var->map_r;
	while (y < var->height)
	{
		x = 0;
		while (x < var->width)
		{
			if (x + 1 != var->width)
		//	{printf("HORIS x: %d y: %d ||| x: %d y: %d\n", map[y][x].x, map[y][x].y, map[y][x].x, map[y][x + 1].y);
				line_draw(var->img, var, map[y][x], map[y][x + 1]);//}
			if (y + 1 != var->height)
		//	{printf("VERTI x: %d y: %d ||| x: %d y: %d\n", map[y][x].x, map[y][x].y, map[y + 1][x].x, map[y][x].y);
				line_draw(var->img, var, map[y + 1][x], map[y][x]);//}
			x++;
		}
		y++;
	}
	printf("-------------------------\n-------------------------\n");
	mlx_put_image_to_window(var->img->mlx_ptr, var->img->mlx_win, var->img->ptr, 50, 50);
}
