/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:40:14 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/21 19:45:35 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
