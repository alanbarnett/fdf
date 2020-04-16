/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:25:11 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/14 02:00:13 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"
#include "draw.h"
#include "fdf_keys.h"
#include "fdf_draw.h"
#include "mlx.h"
#include "ft_mem.h"

#include <unistd.h> //usleep

/*
** Gets the height of the map. Used for centering the map on screen.
*/

static int			get_map_height(int **map)
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
** Scale is an integer that determines my zoom level at this stage. It will be
** multiplied to the x and y offsets of the double array. It is the distance
** between each node of the wireframe.
*/

static struct s_fdf	*fdf_setup(int **map, int width)
{
	struct s_fdf	*data;
	int				endian;

	data = (struct s_fdf *)ft_memalloc(sizeof(struct s_fdf));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "fdf - abarnett");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->img_bits_per_pixel), &(data->img_size_line), &endian);
	data->map = map;
	data->map_width = width;
	data->map_height = get_map_height(map);
	data->scale = SCALE;
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

/*
** Jump table for each function controllable by key press
*/
static int			fdf_keys_jumptable(int keycode, struct s_fdf *data)
{
	static void	(*key_funcs[128])() = {
		[KEY_Q] = quit,
		[KEY_DARR] = rotate_x_neg,
		[KEY_UARR] = rotate_x_pos,
		[KEY_LARR] = rotate_y_neg,
		[KEY_RARR] = rotate_y_pos,
		[KEY_PERIOD] = rotate_z_neg,
		[KEY_COMMA] = rotate_z_pos,
		[KEY_H] = move_left,
		[KEY_L] = move_right,
		[KEY_K] = move_up,
		[KEY_J] = move_down,
		[KEY_I] = zoom_in,
		[KEY_O] = zoom_out,
		[KEY_R] = reset_cam,
	};

	//ft_printf("keycode: %d\n", keycode);
	if (keycode < 128 && key_funcs[keycode])
		key_funcs[keycode](data);
	if (keycode == KEY_LSHIFT)
		data->rotating = !data->rotating;
	draw_image(data);
	return (0);
}

/*
** Carousel function while not doing anything. Toggled by pressing LSHIFT.
*/
int					rotate(struct s_fdf *data)
{
	if (data->rotating == 0)
		return (0);
	rotate_x_pos(data);
	rotate_z_neg(data);
	draw_image(data);
	usleep(ROTATION_SPEED_MS);
	return (0);
}

/*
** Main FDF function. Creates the data struct, draws the image, sets up hooks
** for keyboard functions, and starts the loop.
*/

void				fdf(int **map, int width)
{
	struct s_fdf	*data;

	data = fdf_setup(map, width);
	draw_image(data);
	mlx_key_hook(data->win_ptr, fdf_keys_jumptable, data);
	mlx_loop_hook(data->mlx_ptr, rotate, data);
	mlx_loop(data->mlx_ptr);
}
