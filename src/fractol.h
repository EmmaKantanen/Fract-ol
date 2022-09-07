/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:20:34 by ekantane          #+#    #+#             */
/*   Updated: 2022/08/08 15:10:16 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include "mlx.h"

# define WIN_X 700
# define WIN_Y 500

typedef struct s_frctl1
{
	double			r;
	double			i;
}					t_frctl1;

typedef struct s_frctl2
{
	double			r;
	double			i;
}					t_frctl2;

typedef struct s_frctl3
{
	double			r;
	double			i;
}					t_frctl3;

typedef unsigned char	t_uchar;

typedef struct s_color
{
	t_uchar			r;
	t_uchar			g;
	t_uchar			b;
}					t_color;

typedef struct s_img
{
	void			*self;
	char			*buff;
	int				pixelbits;
	int				linebytes;
	int				endian;
}					t_img;

typedef struct s_dot
{
	t_frctl1	*julia;
	int			(*f1)(struct s_dot *data, int *xy, t_frctl1 *c, t_frctl1 *z);
	t_frctl2	*mandelbrot;
	int			(*f2)(struct s_dot *data, int *xy, t_frctl2 *c, t_frctl2 *z);
	t_frctl3	*tricorn;
	int			(*f3)(struct s_dot *data, int *xy, t_frctl3 *c, t_frctl3 *z);
	double		if_julia;
	double		if_mandelbrot;
	double		if_tricorn;
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	int			imax;
	void		*ptr;
	void		*win;
	t_img		*img;
}				t_dot;

/* main */
int			main(int argc, char **argv);
void		hud(t_dot *d);
int			launch(char *name);
int			pix_on_img(t_img *img, int x, int y, t_color *clr);
/* julia */
t_dot		*initialize_julia(char *name);
int			julia(t_dot *data, int *xy, t_frctl1 *c, t_frctl1 *z);
void		draw_julia(t_dot *data);
t_frctl1	*new_julia(double r, double i);
int			mouse_move(int x, int y, void *data);
/* mandelbrot */
t_dot		*initialize_mandelbrot(char *name);
int			mandelbrot(t_dot *data, int *xy, t_frctl2 *c, t_frctl2 *z);
void		draw_mandelbrot(t_dot *data);
t_frctl2	*new_mandelbrot(double r, double i);
/* tricorn */
t_dot		*initialize_tricorn(char *name);
int			tricorn(t_dot *data, int *xy, t_frctl3 *c, t_frctl3 *z);
void		draw_tricorn(t_dot *data);
t_frctl3	*new_tricorn(double r, double i);
/* color */
t_color		*new_color(int r, int g, int b);
void		give_color(t_color *clr, int iter);
void		zoom_color(int key, t_dot *d);
/* control */
int			deal_key(int key, t_dot *d);
int			mouse_port(int key, int x, int y, void *data);

/* follow_mouse */
void		zoom_in(int key, t_dot *d, int x, int y);
void		zoom_out(int key, t_dot *d);

#endif
