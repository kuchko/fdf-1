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

static void		line_draw(t_img *img, t_var *var, t_point zero, t_point one)
{
	int dx = ABS((one.x - zero.x));
	int dy = ABS((one.y - zero.y));
	int sx = (one.x >= zero.x ? 1 : -1);
	int sy = (one.y >= zero.y ? 1 : -1);
	if (dy <= dx)
	{
		int d = (dy << 1) - dx;
		int d1 = dy << 1;
		int d2 = (dy - dx) << 1;
		pixel_put(img, var, zero.y, zero.y);
		int x = zero.x + sx;
		int y = zero.y;
		int i = 0;
		while (++i <= dx)
		{
			if (d > 0)
			{
				d += d2;
				y += sy;
			}
			else
				d += d1;
			x += sx;
			pixel_put(img, var, x, y);
		}
	}
	else
	{
		int d = (dx << 1) - dy;
		int d1 = dx << 1;
		int d2 = (dx - dy) << 1;
		pixel_put(img, var, zero.y, zero.y);
		int y = zero.y + sy;
		int	x = zero.x;
		int i = 0;
		while(++i <= dy)
		{
			if (d > 0)
			{
				d += d2;
				x += sx;
			}
			else
				d += d1;
			pixel_put(img, var, x, y);
			y += sy;
		}
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
			// {	printf("x: %d, y %d || x: %d y: %d\n", map[y][x].x, map[y][x].y, map[y][x + 1].x, map[y][x + 1].y);
				line_draw(var->img, var, map[y][x], map[y][x + 1]);//}
			if (y + 1 != var->height)
				line_draw(var->img, var, map[y][x], map[y + 1][x]);
			x++;
		}
		y++;
	}
	// printf("-------------------------\n-------------------------\n");
	mlx_put_image_to_window(var->img->mlx_ptr, var->img->mlx_win, var->img->ptr, 50, 50);
}
