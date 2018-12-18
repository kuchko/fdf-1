/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fils_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:06:39 by vrudyka           #+#    #+#             */
/*   Updated: 2018/12/12 20:06:40 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			fils_add(t_fils **fils, t_fils *new)
{
	t_fils			*point;

	point = *fils;
	if (point == NULL)
	{
		*fils = new;
		point = *fils;
	}
	else
	{
		while (point->next != NULL)
			point = point->next;
		point->next = new;
	}
}

static void			fils_new(char **split, t_fils **fils)
{
	static int		x = 0;
	int				y;
	t_fils			*tmp;

	y = -1;
	while (split[++y])
	{
		tmp = (t_fils*)malloc(sizeof(t_fils));
		tmp->x = (double)x;
		tmp->y = (double)y;
		tmp->z = (double)ft_atoi(split[y]);
		tmp->next = NULL;
		fils_add(fils, tmp);
	}
	x++;
}

t_fils				*fils_fill(int fd)
{
	char			*line;
	t_fils			*fils;

	fils = NULL;
	while (get_next_line(fd, &line))
	{
		fils_new(ft_strsplit(line, ' '), &fils);
		free(line);
	}
	return (fils);
}
