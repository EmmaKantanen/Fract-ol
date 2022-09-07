/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/08/08 13:06:36 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	pan(int key, t_dot *d)
{
	double	pan[2];

	pan[0] = (d->xmax - d->xmin) / 42;
	pan[1] = (d->ymax - d->ymin) / 42;
	if (key == 13)
	{
		d->ymin -= pan[0];
		d->ymax -= pan[0];
	}
	if (key == 0)
	{
		d->xmin -= pan[0];
		d->xmax -= pan[0];
	}
	if (key == 1)
	{
		d->ymin += pan[0];
		d->ymax += pan[0];
	}
	else if (key == 2)
	{
		d->xmin += pan[0];
		d->xmax += pan[0];
	}
}

static int	zoom_port(int key, int x, int y, void *data)
{
	t_dot	*d;

	d = (t_dot *)data;
	pan(key, d);
	zoom_color(key, d);
	zoom_in(key, d, x, y);
	zoom_out(key, d);
	mlx_clear_window(d->ptr, d->win);
	if (d->if_julia == 1)
		draw_julia(data);
	if (d->if_mandelbrot == 1)
		draw_mandelbrot(data);
	if (d->if_tricorn == 1)
		draw_tricorn(data);
	mlx_put_image_to_window(d->ptr, d->win, d->img->self, 0, 0);
	hud(data);
	return (1);
}

int	mouse_port(int key, int x, int y, void *data)
{
	t_dot	*d;

	d = (t_dot *)data;
	if (x < 0 || y < 0 || x > WIN_X || y > WIN_Y)
		return (0);
	if (key == 4)
		zoom_port(4, x, y, data);
	if (key == 5)
		zoom_port(5, x, y, data);
	if (d->if_julia == 1)
		draw_julia(data);
	if (d->if_mandelbrot == 1)
		draw_mandelbrot(data);
	if (d->if_tricorn == 1)
		draw_tricorn(data);
	mlx_clear_window(d->ptr, d->win);
	mlx_put_image_to_window(d->ptr, d->win, d->img->self, 0, 0);
	return (1);
}

int	deal_key(int key, t_dot *d)
{
	if (key == 13)
		zoom_port(13, 0, 0, d);
	if (key == 0)
		zoom_port(0, 0, 0, d);
	if (key == 1)
		zoom_port(1, 0, 0, d);
	if (key == 2)
		zoom_port(2, 0, 0, d);
	if (key == 53)
	{
		mlx_destroy_window(d->ptr, d->win);
		mlx_destroy_image(d->ptr, d->img->self);
		exit(0);
	}
	return (0);
}
