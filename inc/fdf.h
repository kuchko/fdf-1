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

# define WIN_HEIGHT 729
# define WIN_WIDTH 1280
# define X_MASK 0
# define ESC 53
# define NUM_PAD_6 88
# include <libft.h>
# include <fcntl.h>
# include "mlx.h"
# include "math.h"

# include <stdio.h> //REMOVE!

typedef	struct		s_img
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*ptr;
	char			*addr;
	int 			bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef	struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef	struct		s_var
{
	int				height;
	int				width;
	int				s_max;
	t_point			**map;
	int				y;
	int				x;
	int				dx;
	int				dy;
	int				err;
	int				derr;
}					t_var;

typedef struct		s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_color;

char				*parsing_fdf(int fd, t_var **var);

t_point				**parsing_line(t_var *var, char *line);

void				display(t_img *img, t_var *var);

int					terminate(int error);

int					X(void *param);

int					terminate(int error);

int					key_down(int key, void *param);

#endif
