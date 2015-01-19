/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:39:31 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/19 16:25:56 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
float	modulus(float zr, float zi)
{
	float	mod;

	mod = sqrt(pow(zr, 2) + pow(zi, 2));
	return (mod);
}

float	x_to_fractal(float x)
{
	t_param	*par;
	float	x_f;

	par = get_params();
	x_f = (x / par->win_size) * (par->x_max - par->x_min) + par->x_min;
	return (x_f);
}

float	y_to_fractal(float y)
{
	t_param	*par;
	float	y_f;

	par = get_params();
	y_f = (y / par->win_size) * (par->y_max - par->y_min) + par->y_min;
	return (y_f);
}

void	draw_fractal(t_disp *d)
{
	float	x;
	float	y;
	t_param	*par;

	par = get_params();
	x = par->x0 - par->win_center;
//	ft_putendl("coucou");
	while (++x < par->x0 + par->win_center)
	{
//		printf("%f\n", x);
		y = par->y0 - par->win_center;
		while (++y < par->y0 + par->win_center)
		{
			if (d->fract == 1)
				mandelbrot(d, par, x, y);
			if (d->fract == 2)
				julia(d, par, x, y);
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
	int		color;
	int		i;
	t_color	rgb;
	float	tmp;
	t_cpx	cpx;

	cpx.zr = par->mod1;
	cpx.zi = par->mod2;
	cpx.cr = x_to_fractal(x / par->zoom);
	cpx.ci = y_to_fractal(y / par->zoom);
	color = 0;
	i = -1;
	while (modulus(cpx.zr, cpx.zi) < 2 && ++i < par->max_iter)
	{
		tmp = cpx.zr * cpx.zr - cpx.zi * cpx.zi + cpx.cr;
		cpx.zi = 2 * cpx.zr * cpx.zi + cpx.ci;
		cpx.zr = tmp;
		color = degrade_blue(&rgb, i, par->max_iter);
	}
	if (i == par->max_iter)
		mlx_pxl_to_image(d->img, x - (par->x0 - par->win_center),
						y - (par->y0 - par->win_center), 0);
	else
		mlx_pxl_to_image(d->img, x - (par->x0 - par->win_center),
						y - (par->y0 - par->win_center), color);
}

void	julia(t_disp *d, t_param *par, float x, float y)
{
	int		color;
	int		i;
	t_color	rgb;
	float	tmp;
	t_cpx	cpx;

	cpx.zr = x_to_fractal(x / par->zoom);
	cpx.zi = y_to_fractal(y / par->zoom);
	cpx.cr = par->mod1;
	cpx.ci = par->mod2;
	color = 0;
	i = -1;
	while (modulus(cpx.zr, cpx.zi) < 2 && ++i < par->max_iter)
	{
		tmp = cpx.zr * cpx.zr - cpx.zi * cpx.zi + cpx.cr;
		cpx.zi = 2 * cpx.zr * cpx.zi + cpx.ci;
		cpx.zr = tmp;
		color = degrade_blue(&rgb, i, par->max_iter);
	}
	if (i == par->max_iter)
		mlx_pxl_to_image(d->img, x - (par->x0 - par->win_center),
						y - (par->y0 - par->win_center), 0);
	else
		mlx_pxl_to_image(d->img, x - (par->x0 - par->win_center),
						y - (par->y0 - par->win_center), color);
}

