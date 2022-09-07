/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/08/08 15:20:01 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Mlx_hook works like this:
mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param).
Mouse movement: x_event = 6. The function will be called like this
(and we also set the starting angle of the fractal): */

int	mouse_move(int x, int y, void *data)
{
	t_dot	*d;

	d = (t_dot *)data;
	if (x < 0 || x > WIN_X || y < 0 || y > WIN_Y)
		return (0);
	d->julia->r = -0.7 + (double)x / 1000;
	d->julia->i = 0.2 + (double)y / 1000;
	draw_julia(d);
	mlx_clear_window(d->ptr, d->win);
	mlx_put_image_to_window(d->ptr, d->win, d->img->self, 0, 0);
	hud(data);
	return (0);
}

/* Here we create a new complex number by creating a combination of a real and
an imaginary number. We start from zeros. */

t_frctl1	*new_julia(double r, double i)
{
	t_frctl1	*ret;

	ret = (t_frctl1 *)malloc(sizeof(t_frctl1));
	ret->r = r;
	ret->i = i;
	return (ret);
}

/* This is where we create the "looping" of the fractal and prevent drawing
happening outside the window. */

void	draw_julia(t_dot *data)
{
	int			xy[2];
	t_frctl1	*z;
	t_color		*clr;

	clr = new_color(0, 0, 0);
	z = new_julia(0, 0);
	xy[0] = -1;
	while (++xy[0] < WIN_X)
	{
		xy[1] = -1;
		while (++xy[1] < WIN_Y)
		{
			give_color(clr, data->f1(data, xy, data->julia, z));
			pix_on_img(data->img, xy[0], xy[1], clr);
		}
	}
	free (clr);
	free (z);
}

/* All the sets are orbital fractals so it's easy to derive Mandelbrot and
Tricorn by using the basic Julia set.

R and i are the real and imaginary numbers of every set and z and c are the
complex numbers.

In the while loop we have the functions for normal Julia sets.
Mandelbrot uses c as a complex parameter and the orbit of the critical point
is 0. Tricorn is a defined in a similar way to the Mandelbrot, but using the
mapping "-2 * tmp * z->i + c->i" instead of "2 * tmp * z->i + c->i". */

int	julia(t_dot *data, int *xy, t_frctl1 *c, t_frctl1 *z)
{
	int			i;
	double		tmp;

	tmp = 0;
	z->r = xy[0] / (WIN_X / (data->xmax - data->xmin)) + data->xmin;
	z->i = xy[1] / (WIN_Y / (data->ymax - data->ymin)) + data->ymin;
	i = -1;
	while (++i < data->imax)
	{
		tmp = z->r;
		z->r = z->r * z->r - z->i * z->i + c->r;
		z->i = 2 * tmp * z->i + c->i;
		if ((z->r * z->r + z->i * z->i) > 4)
			break ;
	}
	return (i);
}

/* Y and X values are the actual size of the fractal and imax is used for the
complexity.  We also need to set an image buffer to create the picture and
mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line,
int *endian) returns information about the created image, allowing it to be
modified later.
*/

t_dot	*initialize_julia(char *name)
{
	t_dot	*d;

	if (ft_strequ(name, "julia") == 0)
		exit (1);
	d = (t_dot *)malloc(sizeof(t_dot));
	if (!d)
		exit (1);
	d->ptr = mlx_init();
	d->win = mlx_new_window(d->ptr, WIN_X, WIN_Y, "Fract'ol: Julia");
	d->xmin = -2;
	d->xmax = 2;
	d->ymin = -1.5;
	d->ymax = 1.5;
	d->imax = 30;
	d->f1 = julia;
	d->julia = new_julia(-0.7, 0.27015);
	d->if_julia = 1;
	d->img = (t_img *)malloc(sizeof(t_img));
	if (!d->img)
		exit (1);
	d->img->self = mlx_new_image(d->ptr, WIN_X, WIN_Y);
	d->img->buff = mlx_get_data_addr(d->img->self, &d->img->pixelbits, \
	&d->img->linebytes, &d->img->endian);
	return (d);
}
