/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/08/07 17:33:40 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* This is whe we create the offset and draw pixels into the image. This
function works pretty much like pixel_put in Minilibx. */

int	pix_on_img(t_img *img, int x, int y, t_color *clr)
{
	img->buff[(y * img->linebytes + x * img->pixelbits / 8) + 0] = clr->b;
	img->buff[(y * img->linebytes + x * img->pixelbits / 8) + 1] = clr->g;
	img->buff[(y * img->linebytes + x * img->pixelbits / 8) + 2] = clr->r;
	return (0);
}

void	hud(t_dot *d)
{
	if (d->if_julia == 1)
		mlx_string_put(d->ptr, d->win, 50, 30, 0xFFFFFF, "Julia");
	if (d->if_mandelbrot == 1)
		mlx_string_put(d->ptr, d->win, 50, 30, 0xFFFFFF, "Mandelbrot");
	if (d->if_tricorn == 1)
		mlx_string_put(d->ptr, d->win, 50, 30, 0xFFFFFF, "Tricorn");
	mlx_string_put(d->ptr, d->win, 60, 50, 0xFFFFFF, "Move: WASD");
	mlx_string_put(d->ptr, d->win, 60, 70, 0xFFFFFF, "Zoom: Mouse scroll");
	mlx_loop(d->ptr);
}

int	launch(char *name)
{
	t_dot	*data;

	data = NULL;
	if (ft_strequ(name, "julia"))
	{
		data = initialize_julia(name);
		draw_julia(data);
		mlx_hook(data->win, 6, 0, mouse_move, (void *)data);
	}
	if (ft_strequ(name, "mandelbrot"))
	{
		data = initialize_mandelbrot(name);
		draw_mandelbrot(data);
	}
	if (ft_strequ(name, "tricorn"))
	{
		data = initialize_tricorn(name);
		draw_tricorn(data);
	}
	mlx_put_image_to_window(data->ptr, data->win, data->img->self, 0, 0);
	mlx_mouse_hook(data->win, mouse_port, (void *)data);
	mlx_key_hook(data->win, deal_key, data);
	hud(data);
	mlx_loop(data->ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	int		ret;

	ret = 0;
	if (argc != 2)
	{
		ft_putstr("usage: ./fractol julia OR mandelbrot OR tricorn\n");
		exit (1);
	}
	if (((ft_strequ(argv[1], "julia") == 0) && (ft_strequ(argv[1], \
	"mandelbrot") == 0) && (ft_strequ(argv[1], "tricorn") == 0)) && (argc == 2))
	{
		ft_putstr("usage: ./fractol julia OR mandelbrot OR tricorn\n");
		exit (1);
	}
	if (argc == 2)
		ret = launch(argv[1]);
	if (!ret)
	{
		ft_putstr("usage: ./fractol julia OR mandelbrot OR tricorn\n");
		exit (1);
	}
	return (0);
}
