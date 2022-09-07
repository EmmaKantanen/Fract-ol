/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/08/07 20:35:21 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(int key, t_dot *d, int x, int y)
{
	double	zoom[2];

	zoom[0] = (d->xmax - d->xmin) / 16;
	zoom[1] = (d->ymax - d->ymin) / 16;
	if (key == 4)
	{
	d->xmin += (zoom[0] * (x / 120));
	d->xmax -= (zoom[0] * (y / 120));
	d->ymax -= (zoom[1] * (x / 120));
	d->ymin += (zoom[1] * (y / 120));
	}
}

void	zoom_out(int key, t_dot *d)
{
	double	zoom[2];

	zoom[0] = (d->xmax - d->xmin) / 16;
	zoom[1] = (d->ymax - d->ymin) / 16;
	if (key == 5)
	{
		d->xmin -= zoom[0];
		d->xmax += zoom[0];
		d->ymax += zoom[1];
		d->ymin -= zoom[1];
	}
}
