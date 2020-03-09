/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 01:43:43 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/08 19:57:13 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_draw.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "mlx.h"
#include <math.h>

/*
** Function to place an (x,y,z) point on a projected 2D plane
**
** Applies transformations based on the position of the camera, and the
** rotation of the coordinate plane
*/

static void	fdf_put_pixel(struct s_fdf *data, double x, double y, double z)
{
	char	*pixel;

	double	new_x;
	double	new_y;
	double	new_z;

	double	theta_x;
	double	theta_y;
	double	theta_z;

	// Converting standard angles to radians
	theta_x = (data->theta_x * M_PI) / 180;
	theta_y = (data->theta_y * M_PI) / 180;
	theta_z = (data->theta_z * M_PI) / 180;
	//

	new_x = x;
	new_y = y;
	new_z = z;

	// Rotations
	// X coordinate
	new_x *= cos(theta_y);
	new_x *= cos(theta_z);
	new_x += y * sin(theta_z);
	// Y coordinate
	new_y *= cos(theta_x);
	new_y *= cos(theta_z);
	new_y -= x * sin(theta_z);
	//

	// Projection
	new_x = new_x + (new_z * sin(theta_y));
	new_y = new_y + (new_z * sin(theta_x));
	//

	new_x += data->cam_x;
	new_y += data->cam_y;

	if (new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT)
		return ;

	pixel = &(data->img_data[ (data->img_size_line * (int)new_y) + ((data->img_bits_per_pixel / 8) * (int)new_x) ]);
	pixel[3] = 0;
	pixel[2] = ft_min(z * 2, 255);
	pixel[1] = 0x20;
	pixel[0] = 0xa0;
}

/*
** Draws a line between start and end
**
** Calculates the length of the 3d line, then walks coordinates with a delta
** variable and plots pixels along the path.
*/

void		fdf_draw_line(struct s_fdf *data, struct s_point start, struct s_point end)
{
	double	x;
	double	y;
	double	z;
	double	d_x;
	double	d_y;
	double	d_z;
	int	steps;

	x = ft_abs(start.x - end.x);
	y = ft_abs(start.y - end.y);
	z = ft_abs(start.z - end.z);
	steps = hypot(x, y);
	steps = hypot(steps, z);
	d_x = ((double)(end.x - start.x) / steps);
	d_y = ((double)(end.y - start.y) / steps);
	d_z = ((double)(end.z - start.z) / steps);
	x = start.x;
	y = start.y;
	z = start.z;
	while (steps)
	{
		fdf_put_pixel(data, x, y, z);
		x += d_x;
		y += d_y;
		z += d_z;
		--steps;
	}
}

/*
** Draws a line from the map into the image, using parameters as coordinates
** into the array. Shift coordinates by half the width and height of the map,
** to center it in the coordinate plane. Then project it by scale to make it
** larger.
*/

void		draw_map_line(struct s_fdf *data, int x1, int x2, int y1, int y2)
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
	fdf_draw_line(data, start, end);
}

/*
** Draw map coordinates into the image
*/

void		draw_map(struct s_fdf *data)
{
	for (int i = 0; data->map[i]; ++i)
	{
		for (int j = 0; j < data->map_width; ++j)
		{
			// draw line forward
			if (j + 1 < data->map_width)
			{
				draw_map_line(data, j, j + 1, i, i);
			}
			// draw line down
			if (data->map[i + 1])
			{
				draw_map_line(data, j, j, i, i + 1);
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
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
