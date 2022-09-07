/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/08/08 15:21:43 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_frctl3	*new_tricorn(double r, double i)
{
	t_frctl3		*ret;

	ret = (t_frctl3 *)malloc(sizeof(t_frctl3));
	ret->r = r;
	ret->i = i;
	return (ret);
}

void	draw_tricorn(t_dot *data)
{
	int			ij[2];
	t_frctl3	*z;
	t_color		*clr;

	clr = new_color(0, 0, 0);
	z = new_tricorn(0, 0);
	ij[0] = -1;
	while (++ij[0] < WIN_X)
	{
		ij[1] = -1;
		while (++ij[1] < WIN_Y)
		{
			give_color(clr, data->f3(data, ij, data->tricorn, z));
			pix_on_img(data->img, ij[0], ij[1], clr);
		}
	}
	free (clr);
	free (z);
}

int	tricorn(t_dot *data, int *xy, t_frctl3 *c, t_frctl3 *z)
{
	int		i;
	double	tmp;

	tmp = 0;
	c->r = xy[0] / (WIN_X / (data->xmax - data->xmin)) + data->xmin;
	c->i = xy[1] / (WIN_Y / (data->ymax - data->ymin)) + data->ymin;
	z->r = 0;
	z->i = 0;
	i = -1;
	while (++i < data->imax)
	{
		tmp = z->r;
		z->r = z->r * z->r - z->i * z->i + c->r;
		z->i = -2 * tmp * z->i + c->i;
		if ((z->r * z->r + z->i * z->i) > 4)
			break ;
	}
	return (i);
}

t_dot	*initialize_tricorn(char *name)
{
	t_dot	*d;

	if (ft_strequ(name, "tricorn") == 0)
		exit (1);
	d = (t_dot *)malloc(sizeof(t_dot));
	if (!d)
		exit (1);
	d->ptr = mlx_init();
	d->win = mlx_new_window(d->ptr, WIN_X, WIN_Y, "Fract'ol: Tricorn");
	d->xmin = -2;
	d->xmax = 2;
	d->ymin = -1.5;
	d->ymax = 1.5;
	d->imax = 30;
	d->f3 = tricorn;
	d->tricorn = new_tricorn(-0.7, 0.27015);
	d->if_tricorn = 1;
	d->img = (t_img *)malloc(sizeof(t_img));
	if (!d->img)
		exit (1);
	d->img->self = mlx_new_image(d->ptr, WIN_X, WIN_Y);
	d->img->buff = mlx_get_data_addr(d->img->self, &d->img->pixelbits, \
	&d->img->linebytes, &d->img->endian);
	return (d);
}
