/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:24:12 by alan              #+#    #+#             */
/*   Updated: 2020/05/01 07:30:15 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_graph.h"
#include "ft_printf.h"
#include <unistd.h> //stderr_fileno
#include <math.h>

static void	show_usage(void)
{
	ft_printfd(STDERR_FILENO, "%s\n%s\n",
			"usage: fdf",
			"Will draw a 3D graph of the compiled function");
}

double			f_z(double x, double y)
{
	return (sin(x) + sin(y));
	//return (cos(x) + cos(y));
}

int			main(void)
{
	show_usage();
	fdf_graph(f_z, M_PI * 2, M_PI * 2);
	return (0);
}
