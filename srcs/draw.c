/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 01:43:43 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/10 20:04:21 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Draws a line from the map into the image, using parameters as coordinates
** into the array. Shift coordinates by half the width and height of the map,
** to center it in the coordinate plane. Then project it by scale to make it
** larger.
*/

void		plot_map_line(struct s_fdf *data, int x1, int x2, int y1, int y2)
{
	struct s_point	start;
	struct s_point	end;

	start.z = data->map[y1][x1] * data->scale;
	end.z = data->map[y2][x2] * data->scale;
	x1 -= (data->map_width / 2);
	x2 -= (data->map_width / 2);
	y1 -= (data->map_height / 2);
	y2 -= (data->map_height / 2);
	start.x = x1 * data->scale;
	start.y = y1 * data->scale;
	end.x = x2 * data->scale;
	end.y = y2 * data->scale;
	fdf_plot_line(data, start, end);
}

/*
** Draw map coordinates into the image
*/

void		plot_map(struct s_fdf *data)
{
	for (int i = 0; data->map[i]; ++i)
	{
		for (int j = 0; j < data->map_width; ++j)
		{
			// draw line forward
			if (j + 1 < data->map_width)
			{
				plot_map_line(data, j, j + 1, i, i);
			}
			// draw line down
			if (data->map[i + 1])
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
