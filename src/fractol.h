/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 08:23:08 by rdestreb          #+#    #+#             */
/*   Updated: 2015/01/27 14:49:31 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <sys/types.h>
# include <sys/uio.h>

# define WIN_SIZE 500
# define MAX_ITER 9

typedef struct s_cpx	t_cpx;
typedef struct s_param	t_param;
typedef struct s_image	t_image;
typedef struct s_color	t_color;
typedef struct s_disp	t_disp;

struct	s_cpx
{
	float	zr;
	float	zi;
	float	cr;
	float	ci;
};

struct	s_param
{
	t_disp	*d;
	float	zoom;
	float	win_size;
	float	center;
	float	x0;
	float	y0;
	float	x_min;
	float	x_max;
	float	y_min;
	float	y_max;
	float	mod1;
	float	mod2;
	int		state;
	int		max_iter;
	int		n;
};

struct	s_image
{
	void	*ptr;
	char	*data;
	int		width;
	int		heigth;
	int		bpp;
	int		endian;
	int		size_line;
};

struct	s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
};

struct	s_disp
{
	void	*mlx;
	void	*win;
	int		fract;
	t_image	*img;
	t_param	*par;
	t_cpx	*c;
	float	win_size;
};

void	wrong_entry(int ac);
void	main_draw(char *fract);
void	create_image(t_disp *d);
void	redraw_image(t_disp *d);
int		motion_hook(int x, int y, t_disp *d);
int		mouse_hook(int button, int x, int y, t_disp *d);
void	mouse_hook2(int button, int x, int y, t_disp *d);
int		key_hook(int keycode, t_disp *d);
void	key_hook2(int keycode, t_disp *d);
int		expose_hook(t_disp *d);
int		mlx_pxl_to_image(t_image *img, int x, int y, int color);
int		degrade_blue(t_color *rgb, int cpt, int max);
int		rgb_to_int(t_color *rgb);
void	init_params(t_disp *d);
t_param	*get_params(void);
void	mandelbrot(t_disp *d, t_param *par, float x, float y);
void	julia(t_disp *d, t_param *par, float x, float y);
void	draw_fractal(t_disp *d);
float	modulus(float zr, float zi);
float	x_to_fractal(float x);
float	y_to_fractal(float y);
void	draw_square(float x, float y, float size);
void	sierpinski(float x, float y, int n, float size);

#endif
