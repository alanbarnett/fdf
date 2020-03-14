/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 01:01:00 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/14 01:59:43 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"
#include <stdlib.h> // exit

void	quit(struct s_fdf *data)
{
	(void)data;
	exit(0);
}

void	rotate_x_neg(struct s_fdf *data)
{
	data->theta_x = (data->theta_x - data->rotation_speed) % 360;
}

void	rotate_x_pos(struct s_fdf *data)
{
	data->theta_x = (data->theta_x + data->rotation_speed) % 360;
}

void	rotate_y_neg(struct s_fdf *data)
{
	data->theta_y = (data->theta_y - data->rotation_speed) % 360;
}

void	rotate_y_pos(struct s_fdf *data)
{
	data->theta_y = (data->theta_y + data->rotation_speed) % 360;
}

void	rotate_z_neg(struct s_fdf *data)
{
	data->theta_z = (data->theta_z - data->rotation_speed) % 360;
}

void	rotate_z_pos(struct s_fdf *data)
{
	data->theta_z = (data->theta_z + data->rotation_speed) % 360;
}

void	move_left(struct s_fdf *data)
{
	data->cam_x -= data->rotation_speed;
}

void	move_right(struct s_fdf *data)
{
	data->cam_x += data->rotation_speed;
}

void	move_up(struct s_fdf *data)
{
	data->cam_y -= data->rotation_speed;
}

void	move_down(struct s_fdf *data)
{
	data->cam_y += data->rotation_speed;
}

void	zoom_in(struct s_fdf *data)
{
	if (data->scale <= 100)
		data->scale += 5;
}

void	zoom_out(struct s_fdf *data)
{
	if (data->scale >= 0)
		data->scale -= 5;
}

void	reset_cam(struct s_fdf *data)
{
	data->scale = SCALE;
	data->cam_x = WIDTH / 2;
	data->cam_y = HEIGHT / 2;
	data->theta_x = 0;
	data->theta_y = 0;
	data->theta_z = 0;
	data->rotation_speed = ROTATION_DEGREES;
}
