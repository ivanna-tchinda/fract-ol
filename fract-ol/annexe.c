/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:02:49 by itchinda          #+#    #+#             */
/*   Updated: 2023/03/06 16:02:50 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_color(char **av)
{
	if (ft_strncmp(av[2], "green", 5) == 0)
		return (0x00081108);
	else if (ft_strncmp(av[2], "purple", 6) == 0)
		return (0x000f0015);
	else if (ft_strncmp(av[2], "blue", 4) == 0)
		return (0x00000315);
	return (0);
}

void	set_values(t_data *data, char **av)
{
	data->x1 = -3;
	data->x2 = 3;
	data->y1 = -2;
	data->y2 = 2;
	if (av[2])
		data->color = ft_color(av);
}

int	get_color(t_data *data, int x, int y)
{
	double	it_max;
	double	color;
	double	i;

	it_max = 120;
	data->xbis = get_pos(x, 0, data);
	data->ybis = get_pos(y, 1, data);
	data->xnew = 0;
	data->ynew = 0;
	i = 0;
	while (data->xnew * data->xnew + data->ynew * data->ynew < 4 && i < it_max)
	{
		data->xold = data->xnew;
		data->yold = data->ynew;
		data->xnew = data->xold * data->xold - data->yold
			* data->yold + data->xbis;
		data->ynew = 2 * data->xold * data->yold + data->ybis;
		i++;
	}
	if (i == it_max)
		color = data->color;
	else
		color = i * data->color;
	return (color);
}

int	get_color_julia(t_data *data, int x, int y)
{
	double	it_max;
	double	color;
	double	i;

	data->xbis = get_pos(x, 0, data);
	data->ybis = get_pos(y, 1, data);
	data->xnew = data->xbis;
	data->ynew = data->ybis;
	i = 0;
	it_max = 120;
	while (data->xnew * data->xnew + data->ynew * data->ynew < 4 && i < it_max)
	{
		data->xold = data->xnew;
		data->yold = data->ynew;
		data->xnew = data->xold * data->xold - data->yold * data->yold - 0.8;
		data->ynew = 2 * data->xold * data->yold + 0.285;
		i++;
	}
	if (i == it_max)
		color = data->color;
	else
		color = i * data->color;
	return (color);
}

void	put_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(int *)dst = get_color(data, x, y);
}
