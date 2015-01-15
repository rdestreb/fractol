/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:39:31 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/15 20:35:42 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
float	modulus(float zr, float zi)
{
	float	mod;

	mod = pow(zr, 2) + pow(zi, 2);
	return (mod);
}

void	draw_fractal(t_disp *d)
{
	float	x;
	float	y;
	t_param	*par;

	par = get_params();
	x = - par->x0;
	ft_putendl("coucou");
	while (++x < par->x0)
	{

		y = - par->y0;
		while (++y < par->y0)
		{
			if (d->fract == 1)
				mandelbrot(d, par, x, y);
			if (d->fract == 2)
			{
				//julia(d, par, x, y);
				ft_putendl("julia");
			}
			if (d->fract == 3)
			{
				//other(d, par, x, y);
				ft_putendl("other");
			}
		}
	}
}

void	mandelbrot(t_disp *d, t_param *par, float x, float y)
{
	int	color;
	int	i;
	t_color	rgb;
	float	tmp;
	t_cpx	cpx;

//	rgb = (t_color *)ft_memalloc(sizeof(t_color));
//	cpx = (t_cpx *)ft_memalloc(sizeof(t_cpx));
	cpx.zr = 1 + par->mod1;
	cpx.zi = 0 + par->mod2;
	cpx.cr = x / par->zoom + 0;
	cpx.ci = y / par->zoom + 0;
	color = 0;
	i = -1;
	while (modulus(cpx.zr, cpx.zi) < 4 && ++i < par->max_iter)
	{
		tmp = cpx.zr * cpx.zr - cpx.zi * cpx.zi + cpx.cr;
		cpx.zi = 2 * cpx.zr * cpx.zi + cpx.ci;
		cpx.zr = tmp;
		color = degrade_blue(&rgb, i);
	}
	if (i == par->max_iter)
		mlx_pxl_to_image(d->img, x + par->x0, y + par->y0, 0);
	else
		mlx_pxl_to_image(d->img, x + par->x0, y + par->y0, color);
//	free(rgb);
//	free(cpx);
}
