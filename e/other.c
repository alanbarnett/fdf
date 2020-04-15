/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 23:03:49 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/17 07:36:12 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies of functions with interesting projections
*/

/*
** Doesn't get z quite right, but it's really cool when paired with the
** rotation function below it, starting out with 0 angle
*/
void		fdf_put_pixel(struct s_fdf *data, int x, int y, int z)
{
	char	*pixel;

	double	new_x;
	double	new_y;

	double	theta_x;
	double	theta_y;
	double	theta_z;

	// Converting standard angles to radians
	theta_x = (data->theta_x * PI) / 180;
	theta_y = (data->theta_y * PI) / 180;
	theta_z = (data->theta_z * PI) / 180;

	new_x = x * cos(theta_y);
	new_x += z * sin(theta_y);
	new_x -= (x * sin(theta_z) + y * sin(theta_z));

	new_y = y * cos(theta_x);
	new_y += z * sin(theta_x);
	new_y -= (y * sin(theta_z) - x * sin(theta_z));

	new_x += data->cam_x;
	new_y += data->cam_y;

	pixel = &(data->img_data[ (data->img_size_line * (int)new_y) + ((data->img_bits_per_pixel / 8) * (int)new_x) ]);
	pixel[3] = 0;
	pixel[2] = ft_min(z * 2, 255);
	pixel[1] = 0x20;
	pixel[0] = 0xa0;
}

int			rotate(struct s_fdf *data)
{
	clear_image(data);
	rotate_x_pos(data);
	rotate_z_neg(data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	usleep(10000);
	return (0);
}


/*
** This clear_image function does really cool things with the colors, when used
** with the rotate function above. It's especially cool if you rotate the x by
** 1.5 times rotation speed, so that it moves a bit more interestingly.
*/

void		clear_image(struct s_fdf *data)
{
	int	size_of_image;

	size_of_image = (WIDTH * HEIGHT * (data->img_bits_per_pixel / 8));
	for (int i = 0; i < size_of_image; ++i)
	{
		data->img_data[i] *= (-1 * (data->theta_x + data->theta_y));
	}
}

/*
** This function prints an allocated fdf map. Useful for debugging
*/

void		print_map(int **map, int size)
{
	for (int i = 0; map[i]; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			ft_printf("%d ", map[i][j]);
		}
		ft_printf("\n");
	}
}

/*
** This is the point plotter used for weird rotate, which does a normal +x -z
** rotate
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
	new_y += x * sin(theta_z);
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
** This is a pixel plotter and reset_cam function for fdf_slow_rotate. The
** struct is also initialized to have a scale of 40, rotation speed of 1, and
** rotation enabled.
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
void	reset_cam(struct s_fdf *data)
{
	data->scale = 40;
	data->cam_x = WIDTH / 2;
	data->cam_y = HEIGHT / 2;
	data->theta_x = 0;
	data->theta_y = 0;
	data->theta_z = 0;
	data->rotation_speed = 1;
}


/*
** This projection makes a really neat flip when used with the previous
** projection as well.
*/
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
	//int				x;
	//int				y;

	// Initialize new point
	new_point.x = point->x;
	new_point.y = point->y;
	new_point.z = point->z;
	//

	// Converting standard angles to radians
	theta.x = (data->theta_x * M_PI) / 180;
	theta.y = (data->theta_y * M_PI) / 180;
	theta.z = (data->theta_z * M_PI) / 180;
	//

	// Rotations
	// X coordinate
	new_point.x *= cos(theta.y);
	new_point.x *= cos(theta.z);
	// Y coordinate
	new_point.y *= cos(theta.x);
	new_point.y *= cos(theta.z);
	// Z coordinate
	new_point.z *= cos(theta.x);
	new_point.z *= cos(theta.y);
	//

	// Projection
	new_point.x = new_point.x + (new_point.z * sin(theta.y));
	new_point.y = new_point.y + (new_point.z * sin(theta.x));
	//

	new_point.x += data->cam_x;
	new_point.y += data->cam_y;
	//new_point.z += data->cam_z;

	// Translate new point to mlx x and y

	if (new_point.x < 0 || new_point.x >= WIDTH || new_point.y < 0 || new_point.y >= HEIGHT)
		return ;

	pixel = &(data->img_data[ (data->img_size_line * (int)new_point.y) + ((data->img_bits_per_pixel / 8) * (int)new_point.x) ]);
	pixel[3] = 0;
	pixel[2] = fmin(point->z * 2, 255);
	pixel[1] = 0x20;
	pixel[0] = 0xa0;
}
