/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:10:07 by vrudyka           #+#    #+#             */
/*   Updated: 2018/12/13 13:10:08 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		lowline(double x, double y, double x1, double y1, t_mlx *mlx)
{
	double		distance;
	double		diffx;
	double		diffy;
	int			flag;

	diffx = x1 - x;
	diffy = y1 - y;
	flag = 1;
	if (diffy < 0)
	{
		flag = -1;
		diffy *= -1;
	}
	distance = (2 * diffy) - diffx;
	printf("low: x %f x1 %f\n", x, x1);
	//mlx_pixel_put(mlx->ptr, mlx->win, x + 50, y + 50, 0x00FFFFFF);
	while (x < x1)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0x00FFFFFF);
		if (distance > 0)
		{
			y = y + flag;
			distance = distance - (2 * diffx);
		}
		distance = distance + (2 * diffy);
		x++;
	}
}

static void		highline(double x, double y, double x1, double y1, t_mlx *mlx)
{
	double		distance;
	int			diffx;
	int			diffy;
	int			flag;

	diffx = x1 - x;
	diffy = y1 - y;
	flag = 1;
	if (diffx < 0)
	{
		flag = -1;
		diffx *= -1;
	}
	distance = (2 * diffx) - diffy;
	printf("high: x %f y %f\n", x, y);
	while (y < y1)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0x00FFFFFF);
		if (distance > 0)
		{
			x = x + flag;
			distance = distance - (2 * diffy);
		}
		distance = distance + (2 * diffx);
		x++;
	}
}

void			line_draw(t_fils *fils, t_mlx *mlx)
{
	t_fils		*point;

	//printf("x: %f | y: %f\n", fils->x, fils->y);
	point = fils;
	if (ABS(point->next->y - point->y) > ABS(point->next->x - point->x)) /*vertical or horizontal*/
	{
		if (point->x > point->next->x) /*if drawing the line downwards*/
			lowline(point->next->x, point->next->y, point->x, point->y, mlx);
		else /*if drawing the line upward*/
			lowline(point->x, point->y, point->next->x, point->next->y, mlx);
	}
	else
	{
		if (point->y > point->next->y) /*drawing the light right*/
			highline(point->next->x, point->next->y, point->x, point->y, mlx);
		else /*drawing the light left*/
			highline(point->x, point->y, point->next->x, point->next->y, mlx);
	}
}
