/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:06:01 by itchinda          #+#    #+#             */
/*   Updated: 2023/03/06 16:06:38 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_data	*init_window(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free (data);
		exit (1);
	}
	data->mlx_win = mlx_new_window(data->mlx, 1200, 800, "Fract-ol");
	data->img = mlx_new_image(data->mlx, 1200, 800);
	data->color = 0x00081108;
	if (!data->mlx_win || !data->img)
		clean_exit(1, data);
	return (data);
}

void	ft_choose_fractal(int ac, char **av)
{
	size_t	i;
	char	*namejulia;

	namejulia = "julia";
	i = 1;
	while ((int)i < ac)
	{
		if (ft_strncmp(av[i], namejulia, 5) == 0)
			set_init_julia(av);
		else
			set_init_mandelbrot(av);
		i++;
	}
}

int	ft_check_colors(char **av)
{
	char	*colors[3];
	size_t	i;

	colors[0] = "green";
	colors[1] = "purple";
	colors[2] = "blue";
	i = 0;
	if (!av[2])
		return (0);
	while (i < 3)
	{
		if (ft_strncmp(av[2], colors[i], ft_strlen(colors[i])) == 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		write(1, colors[i], ft_strlen(colors[i]));
		write(1, "\n", 1);
		i++;
	}
	return (1);
}

int	ft_check_param(char **av)
{
	char	*namejulia;
	char	*namemandel;

	namejulia = "julia";
	namemandel = "mandelbrot";
	if ((ft_strlen(av[1]) != 5 && ft_strlen(av[1]) != 10))
	{
		write(1, "mandelbrot\n", 11);
		write(1, "julia\n", 6);
		return (1);
	}
	if (ft_strncmp(av[1], namejulia, 5) != 0
		&& ft_strncmp(av[1], namemandel, 10) != 0)
	{
		write(1, "mandelbrot\n", 11);
		write(1, "julia\n", 6);
		return (1);
	}
	if (ft_check_colors(av) == 1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac > 3 || ac == 1)
	{
		write(1, "1 or 2 arguments is required\n", 29);
		return (1);
	}
	if (ft_check_param(av) == 1)
	{
		exit(EXIT_SUCCESS);
		return (1);
	}
	ft_choose_fractal(ac, av);
	return (0);
}
