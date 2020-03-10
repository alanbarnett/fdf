/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 06:38:34 by alan              #+#    #+#             */
/*   Updated: 2020/04/29 06:41:26 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_setup.h"
#include "config.h"
#include "ft_mem.h"
#include "mlx.h"

/*
** Creates the mlx connection, window, and image I will be using. Gets the data
** about the image as well, so it is ready to use.
**
** It takes a function pointer to generate z for a 3D graph, as well as the
** width and height (x and y length) of the graph.
**
** Scale is the number that determines how far apart each point is. Steps is
** the amount of points to draw on each axis of the xy graph.
*/

struct s_fdf	*fdf_graph_setup(double (*f_z)(double x, double y), \
						int width, int height)
{
	struct s_fdf	*data;
	int				endian;

	data = (struct s_fdf *)ft_memalloc(sizeof(struct s_fdf));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, WINDOW_NAME);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, \
			&(data->img_bits_per_pixel), &(data->img_size_line), &endian);
	data->f_z = f_z;
	data->width = width;
	data->height = height;
	width = (width > height ? width : height);
	data->scale = ((WIDTH * 0.80) / width);
	data->steps = 100;
	data->rotation_speed = ROTATION_DEGREES;
	data->origin_x = WIDTH / 2;
	data->origin_y = HEIGHT / 2;
	data->cam_x = 0;
	data->cam_y = 0;
	data->theta_x = 0;
	data->theta_y = 0;
	data->theta_z = 0;
	data->rotating = 0;
	return (data);
}
