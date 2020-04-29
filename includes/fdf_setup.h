/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 06:37:24 by alan              #+#    #+#             */
/*   Updated: 2020/04/28 07:10:46 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_SETUP_H
# define FDF_SETUP_H

/*
** Contains things for maintaining the connection with minilibx, as well as
** data about the map and the position/rotation of the coordinate plane.
*/
struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		**map;
	int		map_width;
	int		map_height;
	int		img_bits_per_pixel;
	int		img_size_line;
	int		scale;
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
** Functions for allocating and deallocating an fdf struct
*/
struct s_fdf	*fdf_setup(int **map, int width);
void			*fdf_cleanup(struct s_fdf *data);

#endif
