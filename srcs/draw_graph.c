/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 01:43:43 by abarnett          #+#    #+#             */
/*   Updated: 2020/04/29 06:30:56 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_setup.h"
#include "config.h"
#include "fdf_draw.h"
#include "ft_mem.h"
#include "mlx.h"

/*
** Draws a line from the map into the image, using parameters as coordinates
** into the array. Shift coordinates by half the width and height of the map,
** to center it in the coordinate plane. Then project it by scale to make it
** larger.
*/

static void	draw_graph_line(struct s_fdf *data, \
					double x1, double x2, double y1, double y2)
{
	struct s_point	start;
	struct s_point	end;

	start.z = data->f_z(x1, y1) * data->scale;
	end.z = data->f_z(x2, y2) * data->scale;
	x1 -= (data->width / 2);
	x2 -= (data->width / 2);
	y1 -= (data->height / 2);
	y2 -= (data->height / 2);
	start.x = x1 * data->scale;
	start.y = y1 * data->scale;
	end.x = x2 * data->scale;
	end.y = y2 * data->scale;
	fdf_plot_line(data, &start, &end);
}

/*
** Draw map coordinates into the image
*/

void		draw_graph(struct s_fdf *data)
{
	double	d_x;
	double	d_y;
	double	x;
	double	y;

	d_x = (double)data->width / data->steps;
	d_y = (double)data->height / data->steps;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			// draw line forward
			if (x + d_x < data->width)
			{
				draw_graph_line(data, x, x + d_x, y, y);
			}
			// draw line down
			if (y + d_y < data->height)
			{
				draw_graph_line(data, x, x, y, y + d_y);
			}
			x += d_x;
		}
		y += d_y;
	}
}

/*
** Full image redrawing function
**
** Clears the current image, draws the map into the image, and then puts the
** image to the screen.
*/

int			draw_image_graph(struct s_fdf *data)
{
	ft_bzero(data->img_data, (WIDTH * HEIGHT * (data->img_bits_per_pixel / 8)));
	draw_graph(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
