/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 15:42:55 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/27 12:39:30 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		expose_hook(t_disp *d)
{
	mlx_put_image_to_window(d->mlx, d->win, d->img->ptr, 0, 0);
	return (0);
}

int		motion_hook(int x, int y, t_disp *d)
{
	t_param	*par;

	par = get_params();
	if (x > 0 && x < d->win_size && !(x % 20) && !(par->state % 2))
	{
		par->mod1 = x_to_fractal(x);
		redraw_image(d);
	}
	if (y > 0 && y < d->win_size && !(y % 20) && !(par->state % 2))
	{
		par->mod2 = y_to_fractal(y);
		redraw_image(d);
	}
	return (0);
}

void	main_draw(char *fract)
{
	t_disp	*d;
	t_param	*par;

	d = (t_disp *)ft_memalloc(sizeof(t_disp));
	d->fract = ft_atoi(fract);
	init_params(d);
	par = get_params();
	d->win_size = par->win_size;
	if (!(d->mlx = mlx_init()))
		return ;
	d->win = mlx_new_window(d->mlx, d->win_size, d->win_size, "fract'ol");
	create_image(d);
	draw_fractal(d);
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_key_hook(d->win, key_hook, d);
	mlx_mouse_hook(d->win, mouse_hook, d);
	mlx_hook(d->win, 6, (1L << 6), motion_hook, d);
	mlx_loop(d->mlx);
}
