/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 15:42:55 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/21 19:22:22 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	redraw_image(t_disp *d)
{
	mlx_destroy_image(d->mlx, d->img->ptr);
	create_image(d);
	draw_fractal(d);
	expose_hook(d);
}

int		expose_hook(t_disp *d)
{
	mlx_put_image_to_window(d->mlx, d->win, d->img->ptr, 0, 0);
	return (0);
}

int		key_hook(int keycode, t_disp *d)
{
	t_param	*par;

	par = get_params();
	if (keycode == 65307)
		exit(1);
	if (keycode == 32)
	{
		init_params(d);
		redraw_image(d);
	}
	if (keycode == 65507)
	{
		par->state++;
		if (!(par->state % 2))
			mlx_string_put(d->mlx, d->win, par->center - 50,
							d->win_size - 10, 0xFFFFFF, "Zoom disabled");
		else
			mlx_string_put(d->mlx, d->win, par->center - 50,
							d->win_size - 10, 0xFFFFFF, "Zoom enabled");
	}
	key_hook2(keycode, d);
	return (0);
}

void	key_hook2(int keycode, t_disp *d)
{
	t_param	*par;

	par = get_params();
	if (keycode == 65361)
	{
		par->x0 -= 10;
		redraw_image(d);
	}
	if (keycode == 65362)
	{
		par->y0 -= 10;
		redraw_image(d);
	}
	if (keycode == 65363)
	{
		par->x0 += 10;
		redraw_image(d);
	}
	if (keycode == 65364)
	{
		par->y0 += 10;
		redraw_image(d);
	}
}

int		mouse_hook(int button, int x, int y, t_disp *d)
{
	t_param	*par;
	float	ecart_x;
	float	ecart_y;
	int		moar;

	moar = -1;
	par = get_params();
	if (button == 1 && par->state % 2)
	{
		ecart_x = (par->x0 - (par->center * (par->zoom))) / (par->zoom);
		ecart_y = (par->y0 - (par->center * (par->zoom))) / (par->zoom);
		x = (abs(par->center - x) > 15) ? x : par->center;
		y = (abs(par->center - y) > 15) ? y : par->center;
		ecart_x = (par->zoom == 1) ? (x - par->center) : ecart_x;
		ecart_y = (par->zoom == 1) ? (y - par->center) : ecart_y;
		while (++moar < par->zoom / 10 && par->zoom < 15000)
		{
			par->zoom += 1;
			par->x0 += par->center + ecart_x + (x - par->center) * !(moar);
			par->y0 += par->center + ecart_y + (y - par->center) * !(moar);
		}
		redraw_image(d);
	}
	mouse_hook2(button, x, y, d);
	return (0);
}

void	mouse_hook2(int button, int x, int y, t_disp *d)
{
	t_param	*par;
	float	ecart_x;
	float	ecart_y;
	int		moar;

	moar = -1;
	par = get_params();
	if (button == 3 && par->zoom > 1 && par->state % 2)
	{
		ecart_x = (par->x0 - (par->center * (par->zoom))) / (par->zoom);
		ecart_y = (par->y0 - (par->center * (par->zoom))) / (par->zoom);
		x = (abs(par->center - x) > 15) ? x : par->center;
		y = (abs(par->center - y) > 15) ? y : par->center;
		while (++moar < par->zoom / 10 && par->zoom > 1)
		{
			par->zoom -= 1;
			par->x0 = (par->center * (par->zoom)) + ecart_x * (par->zoom) +
				(x - par->center) * !(moar);
			par->y0 = (par->center * (par->zoom)) + ecart_y * (par->zoom) +
				(y - par->center) * !(moar);
		}
		if (par->zoom == 1)
		{
			par->x0 = par->center;
			par->y0 = par->center;
		}
		redraw_image(d);
	}
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
	mlx_hook(d->win, 6, (1L<<6), motion_hook, d);
	mlx_loop(d->mlx);
}
