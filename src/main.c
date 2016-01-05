/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 13:39:43 by rdestreb          #+#    #+#             */
/*   Updated: 2015/02/16 11:36:55 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_params(t_disp *d)
{
	t_param	*par;

	par = get_params();
	par->d = d;
	par->win_size = WIN_SIZE;
	par->center = par->win_size / 2;
	par->zoom = 1;
	par->state = 0;
	par->x0 = par->center;
	par->y0 = par->center;
	if (d->fract == 1)
	{
		par->x_min = -2;
		par->x_max = 0.5;
	}
	if (d->fract == 2)
	{
		par->x_min = -1.25;
		par->x_max = 1.25;
	}
	par->y_min = -1.25;
	par->y_max = 1.25;
	par->mod1 = 0;
	par->mod2 = 0;
	par->max_iter = 100;
}

t_param	*get_params(void)
{
	static t_param	*par = NULL;

	if (par)
		return (par);
	par = (t_param *)ft_memalloc(sizeof(t_param));
	return (par);
}

void	wrong_entry(int ac)
{
	if (ac > 2)
		ft_putstr_fd("Error : too many arguments.\n", 2);
	else if (ac == 2)
		ft_putstr_fd("Error : wrong entry.\n", 2);
	ft_putstr_fd("Please enter the digit corresponding to", 2);
	ft_putstr_fd(" the fractal you wanna display among :\n", 2);
	ft_putstr_fd(" 1 : Mandelbrot \n 2 : Julia \n 3 : Sierpinski carpet\n", 2);
	exit (1);
}

int		main(int ac, char **av)
{
	if (ac == 2 && (!ft_strcmp(av[1], "1") || !ft_strcmp(av[1], "2")
					|| !ft_strcmp(av[1], "3")))
		main_draw(av[1]);
	else
		wrong_entry(ac);
	return (0);
}
