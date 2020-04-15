/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:58:27 by abarnett          #+#    #+#             */
/*   Updated: 2020/04/15 03:48:58 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"
#include "fdf_draw.h"
#include "mlx.h"
#include <math.h>

/*
** Rotates a point in the point struct by angles (in radians)
**
** This could be optimized by precalculating the sin and cos values for x y z
*/

static void	rotate_point(struct s_point *point, double x, double y, double z)
{
	double	tmp;

	// Converting standard angles to radians
	x = (x * M_PI) / 180;
	y = (y * M_PI) / 180;
	z = (z * M_PI) / 180;
	// X direction
	tmp = point->y;
	point->y *= cos(x);
	point->y -= point->z * sin(x);
	point->z *= cos(x);
	point->z += tmp * sin(x);
	// Y direction
	tmp = point->x;
	point->x *= cos(y);
	point->x -= point->z * sin(y);
	point->z *= cos(y);
	point->z += tmp * sin(y);
	// Z direction
	point->x *= cos(z);
	point->x -= point->y * sin(z);
	point->y *= cos(z);
	point->y += tmp * sin(z);
}

/*
** Function to place an (x,y,z) point on a projected 2D plane
**
** Rotates the point with angles stored in the data struct
** Moves a camera to view the object
*/

void		fdf_plot_point(struct s_fdf *data, struct s_point *point)
{
	char			*pixel;
	struct s_point	new_p;

	// Initialize new point
	new_p.x = point->x;
	new_p.y = point->y;
	new_p.z = point->z;

	// Rotate
	rotate_point(&new_p, data->theta_x, data->theta_y, data->theta_z);

	// Camera adjustment
	new_p.x += data->cam_x;
	new_p.y += data->cam_y;

	// Projection
	new_p.x += new_p.x * (new_p.z / VANISHING_POINT);
	new_p.y += new_p.y * (new_p.z / VANISHING_POINT);

	// Origin adjustment
	// y needs to be inverted, since mlx y points down
	new_p.x += data->origin_x;
	new_p.y = (-1 * new_p.y) + data->origin_y;

	if (new_p.x < 0 || new_p.x >= WIDTH || new_p.y < 0 || new_p.y >= HEIGHT)
		return ;
	if (new_p.z < (VANISHING_POINT * -1))
		return ;

	pixel = &(data->img_data[ (data->img_size_line * (int)new_p.y) + \
			((data->img_bits_per_pixel / 8) * (int)new_p.x) ]);
	pixel[3] = 0;
	pixel[2] = fmin(0x20 + point->z * 2, 255);
	pixel[1] = 0x60 + ((double)0x20 * (new_p.z / VANISHING_POINT));
	pixel[0] = 0x60 + ((double)0xa0 * (new_p.z / VANISHING_POINT));
}

/*
** Draws a line between start and end
**
** Calculates the length of the 3d line, then walks coordinates with a delta
** variable and plots pixels along the path.
*/

void	fdf_plot_line(struct s_fdf *data, struct s_point *start,
						struct s_point *end)
{
	struct s_point	point;
	double			d_x;
	double			d_y;
	double			d_z;
	int				steps;

	point.x = fabs(start->x - end->x);
	point.y = fabs(start->y - end->y);
	point.z = fabs(start->z - end->z);
	steps = hypot(point.x, point.y);
	steps = hypot(steps, point.z);
	d_x = ((end->x - start->x) / steps);
	d_y = ((end->y - start->y) / steps);
	d_z = ((end->z - start->z) / steps);
	point.x = start->x;
	point.y = start->y;
	point.z = start->z;
	while (steps)
	{
		fdf_plot_point(data, &point);
		point.x += d_x;
		point.y += d_y;
		point.z += d_z;
		--steps;
	}
}
