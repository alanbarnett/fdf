/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 01:43:43 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/18 04:12:02 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"
#include "fdf_draw.h"
#include "ft_mem.h"
#include "mlx.h"

/*
** Draws a line from the map into the image
**
** Sets the Z coordinate from the map, applying the scale
** Shifts x and y coordinates to be centered on the origin
** Sets Y to be positive up, instead of positive down (like the array)
** Expands the points by scale
*/

static void	plot_map_line(struct s_fdf *data, int x1, int x2, int y1, int y2)
{
	struct s_point	start;
	struct s_point	end;

	start.z = data->map[y1][x1] * data->scale;
	end.z = data->map[y2][x2] * data->scale;
	start.x = x1 - (data->map_width / 2.0);
	start.y = y1 - (data->map_height / 2.0);
	end.x = x2 - (data->map_width / 2.0);
	end.y = y2 - (data->map_height / 2.0);
	start.y *= -1;
	end.y *= -1;
	start.x *= data->scale;
	start.y *= data->scale;
	end.x *= data->scale;
	end.y *= data->scale;
	fdf_plot_line(data, &start, &end);
}

/*
** Draw map coordinates into the image
*/

void		plot_map(struct s_fdf *data)
{
	for (int i = 0; i < data->map_height; ++i)
	{
		for (int j = 0; j < data->map_width; ++j)
		{
			// draw line forward
			if (j + 1 < data->map_width)
			{
				plot_map_line(data, j, j + 1, i, i);
			}
			// draw line down
			if (i + 1 < data->map_height)
			{
				plot_map_line(data, j, j, i, i + 1);
			}
		}
	}
}

/*
** Full image redrawing function
**
** Clears the current image, draws the map into the image, and then puts the
** image to the screen.
*/

int			draw_image(struct s_fdf *data)
{
	ft_bzero(data->img_data, (WIDTH * HEIGHT * (data->img_bits_per_pixel / 8)));
	plot_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
