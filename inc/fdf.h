/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:20:58 by vrudyka           #+#    #+#             */
/*   Updated: 2018/12/12 16:21:00 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_HEIGHT	576
# define WIN_WIDTH	1024
# include <libft.h>
# include <fcntl.h>
# include "mlx.h"
# include "math.h"

# include <stdio.h> //REMOVE!

typedef	struct		s_image
{
	void			*ptr;
	char			*addr;
	int 			bpp;
	int				size_line;
	int				endian;
}					t_image;

typedef	struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef	struct		s_fils
{
	double			x;
	double			y;
	double			z;
	struct s_fils	*next;
}					t_fils;

t_fils				*fils_fill(int fd);
void				line_draw(t_fils *fils, t_mlx *mlx);

#endif
