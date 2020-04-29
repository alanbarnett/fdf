/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 06:38:34 by alan              #+#    #+#             */
/*   Updated: 2020/04/28 10:54:55 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_setup.h"
#include "config.h"
#include "ft_mem.h"
#include "mlx.h"

/*
** Gets the height of the map. Used for centering the map on screen.
*/

static int		get_map_height(int **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		++i;
	}
	return (i);
}

/*
** Creates the mlx connection, window, and image I will be using. Gets the data
** about the image as well, so it is ready to use.
**
** It takes the width of the map, which should be already known since rows
** aren't null terminated. It can calculate the height from the map, since the
** whole thing is null terminated.
**
** Scale is an integer that determines my zoom level. It will be multiplied to
** the x and y offsets of the double array. It is the distance between each
** node of the wireframe.
*/

struct s_fdf	*fdf_setup(int **map, int width)
{
	struct s_fdf	*data;
	int				endian;

	data = (struct s_fdf *)ft_memalloc(sizeof(struct s_fdf));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, WINDOW_NAME);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, \
			&(data->img_bits_per_pixel), &(data->img_size_line), &endian);
	data->map = map;
	data->map_width = width;
	data->map_height = get_map_height(map);
	width = (width > data->map_height ? width : data->map_height);
	data->scale = ((WIDTH * 0.80) / width);
	data->rotation_speed = ROTATION_DEGREES;
	data->origin_x = WIDTH / 2;
	data->origin_y = HEIGHT / 2;
	data->cam_x = 0;
	data->cam_y = 0;
	data->theta_x = 0;
	data->theta_y = 0;
	data->theta_z = 0;
	data->rotating = 0;
	return (data);
}
