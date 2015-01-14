/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:39:31 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/14 19:32:34 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	modulus(double zr, double zi)
{
	double	mod;

	mod = sqrt(zr * zr + zi * zi);
	return (mod);
}

void	draw_fractal(t_disp *d, char *fract)
{
	double	x;
	double	y;
	t_param	*par;

	par = get_params();
	x = - par->x0;
	while (++x < par->x0)
	{
		y = - par->y0;
		while (++y < d->win_size / 2)
		{
			if (!ft_strcmp(fract, "1"))
				mandelbrot(d, par, x, y);
			if (!ft_strcmp(fract, "2"))
			{
				//julia(d, par, x, y);
				ft_putendl("julia");
			}
			if (!ft_strcmp(fract, "3"))
			{
				//other(d, par, x, y);
				ft_putendl("other");
			}
		}
	}
}

void	mandelbrot(t_disp *d, t_param *par, double x, double y)
{
	int	color;
	int	i;
	t_color	*rgb;
	double	tmp;
	t_cpx	*cpx;

	rgb = (t_color *)ft_memalloc(sizeof(t_color));
	cpx = (t_cpx *)ft_memalloc(sizeof(t_cpx));
	cpx->cr = x / par->zoom - 0.1;
	cpx->ci = y / par->zoom - 0.1;
	i = -1;
	while (modulus(cpx->zr, cpx->zi) < 2 && ++i < par->max_iter)
	{
		tmp = cpx->zr * cpx->zr - cpx->zi * cpx->zi + cpx->cr;
		cpx->zi = 2 * cpx->zr * cpx->zi + cpx->ci;
		cpx->zr = tmp;
		color = degrade_blue(rgb, i);
	}
	if (i == par->max_iter)
		mlx_pxl_to_image(d->img, x + par->x0, y + par->y0, 0);
	else
		mlx_pxl_to_image(d->img, x + par->x0, y + par->y0, color);
	free(rgb);
	free(cpx);
}
