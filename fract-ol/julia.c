/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:05:40 by itchinda          #+#    #+#             */
/*   Updated: 2023/03/06 15:44:20 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_color_julia(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(int *)dst = get_color_julia(data, x, y);
}

void	draw_fractal_julia(t_data *data)
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
			put_color_julia(data, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

int	ft_change_color(t_data *data)
{
	if (data->color == 0x000f0015)
		return (0x00081108);
	else if (data->color == 0x00081108)
		return (0x00000315);
	else
		return (0x000f0015);
	return (0);
}

int	mouse_hook_julia(int button, int x, int y, t_data *data)
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
	draw_fractal_julia(data);
	return (1);
}

void	set_init_julia(char **av)
{
	t_data	*data;

	data = init_window();
	set_values(data, av);
	mlx_hook(data->mlx_win, 2, 1L << 0, close_win, data);
	mlx_hook(data->mlx_win, 17, 0L, mouse_click, data);
	mlx_mouse_hook(data->mlx_win, mouse_hook_julia, data);
	draw_fractal_julia(data);
	mlx_loop(data->mlx);
}
