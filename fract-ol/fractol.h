/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:05:30 by itchinda          #+#    #+#             */
/*   Updated: 2023/03/07 12:52:15 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"
# include <X11/Xlib.h>

typedef struct s_data{
	void	*img;
	char	*addr;
	int		color;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	double	xold;
	double	yold;
	double	xnew;
	double	ynew;
	double	xbis;
	double	ybis;
	double	x1;
	double	x2;
	double	y1;
	double	y2;

}	t_data;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_BUTTONPRESS = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

int		ft_change_color(t_data *data);
void	ft_choose_fractal(int ac, char **av);
void	clean_exit(int exit_code, t_data *data);
int		ft_check_param(char **av);
int		ft_check_goodname(int ac, char **av);
int		close_win(int keycode, t_data *data);
int		mouse_click(t_data *data);
void	put_color(t_data *data, int x, int y);
void	put_color_julia(t_data *data, int x, int y);
void	draw_fractal_julia(t_data *data);
int		mouse_hook_julia(int button, int x, int y, t_data *data);
void	set_init_julia(char **av);
void	draw_fractal_mandelbrot(t_data *data);
int		mouse_hook_mandelbrot(int button, int x, int y, t_data *data);
t_data	*init_window(void);
int		ft_check_colors(char **av);
void	set_init_mandelbrot(char **av);
int		change_color(long double c_zoom, t_data *data);
int		get_color(t_data *data, int x, int y);
void	set_values(t_data *data, char **av);
float	get_pos(int x, int axis, t_data *data);
float	get_new_border(float x, float y, char *type, t_data *data);
int		ft_color(char **av);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_color_julia(t_data *data, int x, int y);

#endif
