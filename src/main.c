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

static t_img	*init_img(void)
{
	t_img		*img;

	img = (t_img *)malloc(sizeof(t_img));
	img->mlx_ptr = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	img->ptr = mlx_new_image(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->size_line, &img->endian);
	mlx_hook(img->mlx_win, 2, 0, key_down, img);
	mlx_hook(img->mlx_win, 17, X_MASK, X, img);
	return (img);
}

int				main(int ac, char **av)
{
	int			fd;
	t_img		*img;
	t_var		*var;

	if ((fd = open(av[1], O_RDONLY)) < 3)
		terminate(70);
	if (ac != 2 || !(ft_strstr(av[1], ".fdf")))
		terminate(85);
	img = init_img();
	var = (t_var*)malloc(sizeof(t_var));
	var->map = parsing_line(var, parsing_fdf(fd, &var));
	display(img, var);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->ptr, 2 * (WIN_WIDTH / (var->height + 4)), 2 * (WIN_HEIGHT / (var->height + 4)));
	mlx_loop(img->mlx_ptr);
	return (0);
}

	//	mlx_string_put(img->mlx_ptr, img->mlx_win, 50, 50, 0xffff00, "kek");
