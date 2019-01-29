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
# define TURN_A 0.1125
# define X_MASK 0

# define ESC 53
# define ARROW_L 123
# define ARROW_R 124
# define ARROW_UP 126
# define MAIN_KEY_R 15
# define MAIN_KEY_B 11
# define MAIN_KEY_G 5

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


typedef struct		s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_color;

typedef	struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef	struct		s_rot
{
	double			x;
	double			y;
	double			z;
}					t_rot;

typedef	struct		s_var
{
	int				height;
	int				width;
	int				s_max;
	int				color;
	int				flag;
	int				sy;
	int				x;
	int				y;
	int				dx;
	int				dy;
	int				err;
	int				derr;
	t_point			**map_o;
	t_point			**map_r;
	t_img			*img;
}					t_var;

char				*parsing_fdf(int fd, t_var **var);

t_point				**parsing_line(t_var *var, char *line);

void				display(t_var *var);

int					terminate(int error);

int					X(void *param);

int					terminate(int error);

int					key_down(int key, t_var *var);

void				rotate(t_var *var, char axis, t_rot **rot);

void				color_assign(t_var *var, int key);

#endif
