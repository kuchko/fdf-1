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

static void		key_init(t_var *var)
{
	mlx_hook(var->img->mlx_win, 2, X_MASK, key_down, var);
	mlx_hook(var->img->mlx_win, 17, X_MASK, termin, var);
}

static t_img	*init_img(void)
{
	t_img		*img;

	img = (t_img *)malloc(sizeof(t_img));
	img->mlx_ptr = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	img->ptr = mlx_new_image(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->size_line, &img->endian);
	return (img);
}

int				main(int ac, char **av)
{
	int			fd;
	t_var		*var;

	if ((fd = open(av[1], O_RDONLY)) < 3)
		terminate("No such file");
	if (ac != 2 || !(ft_strstr(av[1], ".fdf")))
		terminate("usage: ./fdf [file_name.fdf]");
	var = (t_var*)malloc(sizeof(t_var));
	var->map_o = parsing_line(var, parsing_fdf(fd, &var));
	var->img = init_img();
	var->flag = 0;
	var->color = 0x27AEE3;
	key_init(var);
	display(var);
	mlx_loop(var->img->mlx_ptr);
	return (0);
}
