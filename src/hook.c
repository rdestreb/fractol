/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:25:55 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/21 20:48:19 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
//		if (par->zoom == 1)
		//	{
		//par->x0 = par->center;
		//	par->y0 = par->center;
		//}
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
