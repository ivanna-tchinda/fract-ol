/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:05:53 by itchinda          #+#    #+#             */
/*   Updated: 2023/03/06 15:49:21 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal_mandelbrot(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		clean_exit(1, data);
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			put_color(data, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

float	get_pos(int x, int axis, t_data *data)
{
	double	c;

	if (axis == 0)
		c = ((float)x * (data->x2 - data->x1) / (float)WIN_WIDTH + data->x1);
	if (axis == 1)
		c = ((float)x * (data->y2 - data->y1) / (float)WIN_HEIGHT + data->y1);
	return (c);
}

float	get_new_border(float x, float y, char *type, t_data *data)
{
	if (ft_strncmp(type, "zoom_in_x1", 10) == 0)
		return (data->x1 - (0.25 * (data->x1 - x)));
	else if (ft_strncmp(type, "zoom_in_x2", 10) == 0)
		return (data->x2 - (0.25 * (data->x2 - x)));
	else if (ft_strncmp(type, "zoom_in_y1", 10) == 0)
		return (data->y1 - (0.25 * (data->y1 - y)));
	else if (ft_strncmp(type, "zoom_in_y2", 10) == 0)
		return (data->y2 - (0.25 * (data->y2 - y)));
	else if (ft_strncmp(type, "zoom_out_x1", 11) == 0)
		return (data->x1 + (0.25 * (data->x1 - x)));
	else if (ft_strncmp(type, "zoom_out_x2", 11) == 0)
		return (data->x2 + (0.25 * (data->x2 - x)));
	else if (ft_strncmp(type, "zoom_out_y1", 11) == 0)
		return (data->y1 + (0.25 * (data->y1 - y)));
	else if (ft_strncmp(type, "zoom_out_y2", 11) == 0)
		return (data->y2 + (0.25 * (data->y2 - y)));
	else
		return (0);
}

int	mouse_hook_mandelbrot(int button, int x, int y, t_data *data)
{
	double	xbis;
	double	ybis;

	xbis = get_pos(x, 0, data);
	ybis = get_pos(y, 1, data);
	if (button == 1)
		data->color = ft_change_color(data);
	if (button == 4)
	{
		data->x1 = get_new_border(xbis, ybis, "zoom_in_x1", data);
		data->x2 = get_new_border(xbis, ybis, "zoom_in_x2", data);
		data->y1 = get_new_border(xbis, ybis, "zoom_in_y1", data);
		data->y2 = get_new_border(xbis, ybis, "zoom_in_y2", data);
	}
	else if (button == 5)
	{
		data->x1 = get_new_border(xbis, ybis, "zoom_out_x1", data);
		data->x2 = get_new_border(xbis, ybis, "zoom_out_x2", data);
		data->y1 = get_new_border(xbis, ybis, "zoom_out_y1", data);
		data->y2 = get_new_border(xbis, ybis, "zoom_out_y2", data);
	}
	draw_fractal_mandelbrot(data);
	return (1);
}

void	set_init_mandelbrot(char **av)
{
	t_data	*data;

	data = init_window();
	set_values(data, av);
	mlx_hook(data->mlx_win, 2, 1L << 0, close_win, data);
	mlx_hook(data->mlx_win, 17, 0L, mouse_click, data);
	mlx_mouse_hook(data->mlx_win, mouse_hook_mandelbrot, data);
	draw_fractal_mandelbrot(data);
	mlx_loop(data->mlx);
}
