/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 06:37:24 by alan              #+#    #+#             */
/*   Updated: 2020/04/29 06:38:42 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_SETUP_H
# define FDF_SETUP_H

/*
** Contains things for maintaining the connection with minilibx, as well as a
** function for generating z and the position/rotation of the coordinate plane.
*/
struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	double	(*f_z)(double x, double y);
	int		width;
	int		height;
	int		img_bits_per_pixel;
	int		img_size_line;
	int		scale;
	int		steps;
	int		rotation_speed;
	int		origin_x;
	int		origin_y;
	int		cam_x;
	int		cam_y;
	int		theta_x;
	int		theta_y;
	int		theta_z;
	int		rotating;
};

/*
** Function for allocating an fdf struct
*/
struct s_fdf	*fdf_graph_setup(double (*f_z)(double x, double y), \
						int width, int height);

#endif
