/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 15:49:11 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/14 19:45:55 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		rgb_to_int(t_color *rgb)
{
	unsigned int	color;

	color = rgb->r << 16;
	color += rgb->g << 8;
	color += rgb->b;
    return (color);
}

int		degrade_blue(t_color *rgb, int cpt)
{
	unsigned int	color;

//	cpt *= 10;
	if (cpt == 0)
		rgb->b = 255;
	if (cpt > 0 && cpt <= 255)
		rgb->r++;
	if (cpt > 255 && cpt <= 510)
		rgb->b--;
	if (cpt > 510 && cpt <= 765)
		rgb->g++;
	if (cpt > 765 && cpt <= 1020)
		rgb->r--;
    if (cpt > 1020 && cpt <= 1275)
		rgb->b++;
	if (cpt > 1275 && rgb->g > 0)
		rgb->g--;
	color = rgb_to_int(rgb);
    return (color);
}

int		mlx_pxl_to_image(t_image *img, int x, int y, int color)
{
	int	octets;

	octets = img->bpp / 8;
	if (x > 0 && x < img->width && y > 0 && y < img->heigth)
		ft_memcpy(&img->data[octets * (x + img->size_line / octets * y)]
					, &color, octets);
	return (0);
}

void	create_image(t_disp *d)
{
	d->img = (t_image *)ft_memalloc(sizeof(t_image));
	d->img->width = d->win_size;
	d->img->heigth = d->win_size;
	d->img->ptr = mlx_new_image(d->mlx, d->img->width, d->img->heigth);
	d->img->data = mlx_get_data_addr(d->img->ptr, &d->img->bpp,
									&d->img->size_line, &d->img->endian);
}

