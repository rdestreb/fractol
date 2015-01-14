/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 15:42:55 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/14 18:13:47 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		expose_hook(t_disp *d)
{

	mlx_put_image_to_window(d->mlx, d->win, d->img->ptr, 0, 0);
	return (0);
}

int		key_hook(int keycode, t_disp *d)
{
//	t_param*par;

//	par = get_params();
	if (keycode == 65307)
		exit(1);
/*	if (keycode == 65361)
		par->x0 -= 10;
	if (keycode == 65362)
		par->y0 -= 10;
	if (keycode == 65363)
		par->x0 += 10;
	if (keycode == 65364)
		par->y0 += 10;
	if (keycode == 65367 && par->cst > 0)
		par->cst -= 0.1;
	if (keycode == 65360 && par->cst < 2)
		par->cst += 0.1;
	if (keycode == 65365 && par->cst2 < 2)
		par->cst2 += 0.1;
	if (keycode == 65366 && par->cst2 > 0)
		par->cst2 -= 0.1;
*/	mlx_clear_window(d->mlx, d->win);
	expose_hook(d);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_disp *d)
{
	x = x;
	y = y;
	button = button;
	d = d;
/*	t_param*par;

	par = get_params();
	if (button == 3)
		par->proj += 1;
	if (button == 4 && par->zoom < 100)
		par->zoom += 1;
	if (button == 5 && par->zoom > 0)
		par->zoom -= 1;
	mlx_clear_window(d->mlx, d->win);
	expose_hook(d);
*/	return (0);
}

int		motion_hook(int x, int y, t_disp *d)
{
	x = x;
	y = y;
	(void)d;
/*	if (x > 0 && x < d->win_size)
		d->par->x0 = x;
	if (y > 0 && y < d->win_size)
		d->par->y0 = y;
	mlx_clear_window(d->mlx, d->win);
	expose_hook(d);
*/	return (0);
}

void	main_draw(char *fract)
{
	t_disp	*d;

	d = (t_disp *)ft_memalloc(sizeof(t_disp));
	d->win_size = 1000;
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->win_size, d->win_size, "fract'ol");
	init_params(d);
	create_image(d);
	draw_fractal(d, fract);
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_key_hook(d->win, key_hook, d);
	mlx_mouse_hook(d->win, mouse_hook, d);
	mlx_hook(d->win, 2, (1L<<0), key_hook, d);
	mlx_hook(d->win, 6, (1L<<6), motion_hook, d);
	mlx_loop(d->mlx);
}
