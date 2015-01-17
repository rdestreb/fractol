/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:39:31 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/17 17:36:03 by rdestreb         ###   ########.fr       */
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

float	x_to_fractal(float x)
{
	t_param	*par;
	float	x_f;

	par = get_params();
	x_f = ((x + par->x0) / par->win_size) * (par->x_max - par->x_min) + par->x_min;
	return (x_f);
}

float	y_to_fractal(float y)
{
	t_param	*par;
	float	y_f;

	par = get_params();
	y_f = ((y + par->y0) / par->win_size) * (par->y_max - par->y_min) + par->y_min;
	return (y_f);
}

void	draw_fractal(t_disp *d)
{
	float	x;
	float	y;
	t_param	*par;

	par = get_params();
	x = - par->x0;
//	ft_putendl("coucou");
	while (++x < par->x0)
	{
//		printf("%f\n", x_to_fractal(x));
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
	cpx.zr = par->mod1;
	cpx.zi = par->mod2;
	cpx.cr = x_to_fractal(x / par->zoom);
	cpx.ci = y_to_fractal(y / par->zoom);
	color = 0;
	i = -1;
	while (modulus(cpx.zr, cpx.zi) < 4 && ++i < par->max_iter)
	{
		tmp = cpx.zr * cpx.zr - cpx.zi * cpx.zi + cpx.cr;
		cpx.zi = 2 * cpx.zr * cpx.zi + cpx.ci;
		cpx.zr = tmp;
		color = degrade_blue(&rgb, i, par->max_iter);
	}
	if (i == par->max_iter)
		mlx_pxl_to_image(d->img, x + par->x0, y + par->y0, 0);
	else
		mlx_pxl_to_image(d->img, x + par->x0, y + par->y0, color);
//	free(rgb);
//	free(cpx);
}
