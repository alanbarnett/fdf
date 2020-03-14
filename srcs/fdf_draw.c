/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:58:27 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/14 02:11:59 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"
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

void	fdf_plot_pixel(struct s_fdf *data, struct s_point *point)
{
	char			*pixel;
	struct s_point	new_point;
	struct s_point	theta;

	// Converting standard angles to radians
	theta.x = (data->theta_x * M_PI) / 180;
	theta.y = (data->theta_y * M_PI) / 180;
	theta.z = (data->theta_z * M_PI) / 180;
	//

	new_point.x = point->x;
	new_point.y = point->y;
	new_point.z = point->z;

	// Rotations
	// X coordinate
	new_point.x *= cos(theta.y);
	new_point.x *= cos(theta.z);
	new_point.x += point->y * sin(theta.z);
	// Y coordinate
	new_point.y *= cos(theta.x);
	new_point.y *= cos(theta.z);
	new_point.y -= point->x * sin(theta.z);
	// Z coordinate

	//

	// Projection
	new_point.x = new_point.x + (new_point.z * sin(theta.y));
	new_point.y = new_point.y + (new_point.z * sin(theta.x));
	//

	new_point.x += data->cam_x;
	new_point.y += data->cam_y;

	if (new_point.x < 0 || new_point.x >= WIDTH || new_point.y < 0 || new_point.y >= HEIGHT)
		return ;

	pixel = &(data->img_data[ (data->img_size_line * (int)new_point.y) + ((data->img_bits_per_pixel / 8) * (int)new_point.x) ]);
	pixel[3] = 0;
	pixel[2] = ft_min(point->z * 2, 255);
	pixel[1] = 0x20;
	pixel[0] = 0xa0;
}

/*
** Draws a line between start and end
**
** Calculates the length of the 3d line, then walks coordinates with a delta
** variable and plots pixels along the path.
*/

void	fdf_plot_line(struct s_fdf *data, struct s_point start, struct s_point end)
{
	struct s_point	point;
	double			d_x;
	double			d_y;
	double			d_z;
	int				steps;

	point.x = ft_abs(start.x - end.x);
	point.y = ft_abs(start.y - end.y);
	point.z = ft_abs(start.z - end.z);
	steps = hypot(point.x, point.y);
	steps = hypot(steps, point.z);
	d_x = ((double)(end.x - start.x) / steps);
	d_y = ((double)(end.y - start.y) / steps);
	d_z = ((double)(end.z - start.z) / steps);
	point.x = start.x;
	point.y = start.y;
	point.z = start.z;
	while (steps)
	{
		fdf_plot_pixel(data, &point);
		point.x += d_x;
		point.y += d_y;
		point.z += d_z;
		--steps;
	}
}
