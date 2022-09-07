/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/07/22 18:02:01 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Steps indicate how "full" the fractal is when specific iterations are
occurring and these ups and downs of complexity happen at the same time the
fractal is being scrolled.*/

void	zoom_color(int key, t_dot *d)
{
	int	step;

	step = 8;
	if (d->imax > 100)
		step = 5;
	else if (d->imax > 142)
		step = 3;
	else if (d->imax > 200)
		step = 1;
	if (key == 4)
		d->imax += step;
	else if (key == 5)
		d->imax -= step;
	if (d->imax < 20)
		d->imax = 20;
}

/* Basically, the more divination in the iteration, the more contrast in the
fractal color. In unsigned char there are 8 data bits like in a hex code. */

void	give_color(t_color *clr, int iter)
{
	clr->r = (90 + (iter * 16)) % 255;
	clr->g = (30 + (iter * 16)) % 255;
	clr->b = (50 - (iter * 12)) % 255;
}

t_color	*new_color(int r, int g, int b)
{
	t_color	*c;

	c = (t_color *)malloc(sizeof(t_color));
	c->r = r;
	c->g = g;
	c->b = b;
	return (c);
}
