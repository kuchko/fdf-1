/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:02:35 by vrudyka           #+#    #+#             */
/*   Updated: 2019/02/06 15:53:08 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				update(t_var *var)
{
	t_img		*img;

	img = var->img;
	ft_bzero(img->addr, WIN_WIDTH * WIN_HEIGHT * 4);
	display(var);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->ptr, 0, 0);
	return (0);
}

void			key_init(t_var *var)
{
	t_img		*img;

	img = var->img;
	mlx_hook(img->mlx_win, 2, 5, key_down, var);
	mlx_hook(img->mlx_win, 17, X_MASK, termin, var);
	mlx_loop(img->mlx_ptr);
}

static t_img	*init_img(char *str)
{
	t_img		*img;

	img = (t_img *)malloc(sizeof(t_img));
	img->mlx_ptr = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, str);
	img->ptr = mlx_new_image(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
	return (img);
}

static t_var	*init_var(int fd, char *str)
{
	int			move_x;
	int			move_y;
	t_var		*var;

	var = (t_var*)malloc(sizeof(t_var));
	parsing_line(var, parsing_fdf(fd, &var));
	var->img = init_img(str);
	move_x = ((((WIN_WIDTH / var->s_max) - var->width) * var->s_max) / 2) + ((WIN_WIDTH % var->s_max) / 2);
	move_y = ((((WIN_HEIGHT / var->s_max) - var->height) * var->s_max) / 2) + ((WIN_HEIGHT % var->s_max) / 2);
	var->scale_x = ((var->width * var->s_max) / 2) + move_x;
	var->scale_y = ((var->height * var->s_max) / 2) + move_y;
	return (var);
}

int				main(int ac, char **av)
{
	int			fd;
	t_var		*var;

	if ((fd = open(av[1], O_RDONLY)) < 3)
		terminate("No such file");
	if (ac != 2 || !(ft_strstr(av[1], ".fdf")))
		terminate("usage: ./fdf [file_name.fdf]");
	var = init_var(fd, av[1]);
	update(var);
	key_init(var);
	return (0);
}
