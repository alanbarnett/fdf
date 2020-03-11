/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:07:28 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/10 19:55:51 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** The width and height of the window.
** These are used a fair amount in calculations as well, to ensure I don't draw
** outside the window and to center the camera.
*/
# define WIDTH 2000
# define HEIGHT 1200

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
** Takes a filename and converts it into a double array for an fdf map.
*/
int		**file_to_fdf_map(const char *filename, int *size);

void	fdf(int **map, int width);

#endif
