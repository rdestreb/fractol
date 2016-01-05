/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:25:55 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/27 12:38:01 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_hook2(int keycode, t_disp *d)
{
	t_param	*par;

	par = get_params();
	if (keycode == 123)
	{
		par->x0 -= 10;
		redraw_image(d);
	}
	if (keycode == 125)
	{
		par->y0 -= 10;
		redraw_image(d);
	}
	if (keycode == 124)
	{
		par->x0 += 10;
		redraw_image(d);
	}
	if (keycode == 126)
	{
		par->y0 += 10;
		redraw_image(d);
	}
}

int		key_hook(int keycode, t_disp *d)
{
	t_param	*par;

	par = get_params();
	if (keycode == 53)
		exit(1);
	if (keycode == 36)
	{
		init_params(d);
		redraw_image(d);
	}
	if (keycode == 49)
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

void	center(t_param *par)
{
	if (par->zoom == 1)
	{
		par->x0 = par->center;
		par->y0 = par->center;
	}
}

void	mouse_hook2(int button, int x, int y, t_disp *d)
{
	t_param	*par;
	float	ecart_x;
	float	ecart_y;
	int		moar;

	moar = -1;
	par = get_params();
	if (button == 5 && par->zoom > 1 && par->state % 2)
	{
		ecart_x = (par->x0 - (par->center * (par->zoom))) / (par->zoom);
		ecart_y = (par->y0 - (par->center * (par->zoom))) / (par->zoom);
		x = (fabsf(par->center - x) > 15) ? x : par->center;
		y = (fabsf(par->center - y) > 15) ? y : par->center;
		while (++moar < par->zoom / 10 && par->zoom > 1)
		{
			par->zoom -= 1;
			par->x0 = (par->center * (par->zoom)) + ecart_x * (par->zoom) +
						(x - par->center) * !(moar);
			par->y0 = (par->center * (par->zoom)) + ecart_y * (par->zoom) +
						(y - par->center) * !(moar);
		}
		center(par);
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
	if (button == 4 && par->state % 2)
	{
		ecart_x = (par->x0 - (par->center * (par->zoom))) / (par->zoom);
		ecart_y = (par->y0 - (par->center * (par->zoom))) / (par->zoom);
		x = (fabsf(par->center - x) > 15) ? x : par->center;
		y = (fabsf(par->center - y) > 15) ? y : par->center;
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
