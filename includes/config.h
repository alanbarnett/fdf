/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:07:28 by alan              #+#    #+#             */
/*   Updated: 2020/04/28 06:42:06 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_CONFIG_H
# define FDF_CONFIG_H

/*
** This is the config file for the features of my fdf
*/

/*
** The name of the window that gets created
*/
# define WINDOW_NAME "fdf - abarnett"

/*
** The width and height of the window.
** These are used a fair amount in calculations as well, to ensure I don't draw
** outside the window and to center the camera.
*/
# define WIDTH (1000)
# define HEIGHT (800)

/*
** The base amount of rotation degrees per keypress
*/
# define ROTATION_DEGREES (2)

/*
** The amount of milliseconds for each frame while in the rotation function
*/
# define ROTATION_SPEED_MS (20000)

/*
** Default scale (distance between points in the file)
*/
# define SCALE (30)

/*
** Multiplier for how much z affects the projected point's x and y value
** i.e. the value (1000) says that with a z of 1000, the projected x and y
** value should double
*/
# define VANISHING_POINT (8000)

#endif
