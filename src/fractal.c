/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:39:31 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/21 20:36:52 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_disp *d)
{
	float	x;
	float	y;
	t_param	*par;

	par = get_params();
	if (d->fract == 3)
		sierpinski(d, par->center, par->center, 1, d->win_size);
	else
	{
		x = par->x0 - par->center;
		while (++x < par->x0 + par->center)
		{
			y = par->y0 - par->center;
			while (++y < par->y0 + par->center)
			{
				if (d->fract == 1)
					mandelbrot(d, par, x, y);
				if (d->fract == 2)
					julia(d, par, x, y);
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
	while (modulus(cpx.zr, cpx.zi) < 4.0 && ++i < par->max_iter)
	{
		tmp = cpx.zr * cpx.zr - cpx.zi * cpx.zi + cpx.cr;
		cpx.zi = 2 * cpx.zr * cpx.zi + cpx.ci;
		cpx.zr = tmp;
		color = degrade_blue(&rgb, i, par->max_iter);
	}
	if (i == par->max_iter)
		mlx_pxl_to_image(d->img, x - (par->x0 - par->center),
						y - (par->y0 - par->center), 0);
	else
		mlx_pxl_to_image(d->img, x - (par->x0 - par->center),
						y - (par->y0 - par->center), color);
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
	while (modulus(cpx.zr, cpx.zi) < 4.0 && ++i < par->max_iter)
	{
		tmp = cpx.zr * cpx.zr - cpx.zi * cpx.zi + cpx.cr;
		cpx.zi = 2 * cpx.zr * cpx.zi + cpx.ci;
		cpx.zr = tmp;
		color = degrade_blue(&rgb, i, par->max_iter);
	}
	if (i == par->max_iter)
		mlx_pxl_to_image(d->img, x - (par->x0 - par->center),
						y - (par->y0 - par->center), 0);
	else
		mlx_pxl_to_image(d->img, x - (par->x0 - par->center),
						y - (par->y0 - par->center), color);
}

void	draw_square(t_disp *d, float x, float y, float size)
{
	float	i;
	float	j;
	t_param	*par;

	par = get_params();
	if ((x + size) * par->zoom > 0 && (x - size) * par->zoom < d->win_size &&
		(y + size) * par->zoom > 0 && (y - size) * par->zoom < d->win_size)
	{
		i = (x - size) * par->zoom;
		while (++i < (x + size) * par->zoom)
		{
			j = (y - size) * par->zoom;
			while (++j < (y + size) * par->zoom)
			{
				mlx_pxl_to_image(d->img, i, j, 0xff6600);
			}
		}
	}
}

void	sierpinski(t_disp *d, float x, float y, int n, float size)
{
	t_param	*par;

	par = get_params();
	draw_square(d, x - (par->x0 - par->center) / par->zoom,
				y - (par->y0 - par->center) / par->zoom, size / 6.0);
	if (n < MAX_ITER)
	{
		size /= 3.0;
		sierpinski(d, x + size, y + size, n + 1, size);
		sierpinski(d, x + size, y, n + 1, size);
		sierpinski(d, x + size, y - size, n + 1, size);
		sierpinski(d, x, y + size, n + 1, size);
		sierpinski(d, x, y - size, n + 1, size);
		sierpinski(d, x - size, y + size, n + 1, size);
		sierpinski(d, x - size, y, n + 1, size);
		sierpinski(d, x - size, y - size, n + 1, size);
	}
}
