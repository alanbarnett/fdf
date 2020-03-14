/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:25:11 by abarnett          #+#    #+#             */
/*   Updated: 2020/05/01 12:17:13 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_setup.h"
#include "config.h"
#include "draw.h"
#include "fdf_keys.h"
#include "mlx.h"

/*
** Jump table for each function controllable by key press
*/

# ifdef __linux__

static int			fdf_keys_jumptable(int keycode, struct s_fdf *data)
{
	static void	(*key_funcs[128])() = {
		[KEY_Q] = quit,
		[KEY_U] = rotate_x_neg,
		[KEY_E] = rotate_x_pos,
		[KEY_I] = rotate_y_neg,
		[KEY_N] = rotate_y_pos,
		[KEY_PERIOD] = rotate_z_neg,
		[KEY_COMMA] = rotate_z_pos,
		[KEY_H] = move_left,
		[KEY_L] = move_right,
		[KEY_K] = move_up,
		[KEY_J] = move_down,
		[KEY_PLUS] = zoom_in,
		[KEY_MINUS] = zoom_out,
		[KEY_R] = reset_cam,
	};

	if (keycode < 128 && key_funcs[keycode])
		key_funcs[keycode](data);
	if (keycode == KEY_LSHIFT)
		data->rotating = !data->rotating;
	draw_image(data);
	return (0);
}

# elif defined __APPLE__

static int			fdf_keys_jumptable(int keycode, struct s_fdf *data)
{
	static void	(*key_funcs[128])() = {
		[KEY_Q] = quit,
		[KEY_UARR] = rotate_x_neg,
		[KEY_DARR] = rotate_x_pos,
		[KEY_RARR] = rotate_y_neg,
		[KEY_LARR] = rotate_y_pos,
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

	if (keycode < 128 && key_funcs[keycode])
		key_funcs[keycode](data);
	if (keycode == KEY_LSHIFT)
		data->rotating = !data->rotating;
	draw_image(data);
	return (0);
}

# else

static int			fdf_keys_jumptable(int keycode, struct s_fdf *data)
{
	(void)keycode;
	(void)data;
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
