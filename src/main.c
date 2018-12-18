/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:02:35 by vrudyka           #+#    #+#             */
/*   Updated: 2018/12/12 12:39:52 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(int ac, char **av)
{
	int			fd;
	t_mlx		*mlx;
	t_fils		*fils;
	t_image		*image;

	fd = 0;
	if (!(fd = open(av[1], O_RDONLY)) && ac != 2)
		return (0);
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))) ||
			!(image = (t_image *)malloc(sizeof(t_image))))
		return (0);
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

	image->ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	image->addr = mlx_get_data_addr(image->ptr, &image->bpp, &image->size_line, &image->endian);

	//fils = fils_fill(fd);
	line_draw(fils, mlx);

	mlx_loop(mlx->ptr);
	close(fd);
	return (0);
}

// 	mlx_key_hook(win, deal_key, (void *)0);
