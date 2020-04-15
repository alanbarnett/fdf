/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:07:28 by alan              #+#    #+#             */
/*   Updated: 2020/04/15 04:29:52 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_CONFIG_H
# define FDF_CONFIG_H

/*
** This is the config file for the features of my fdf
*/

/*
** The width and height of the window.
** These are used a fair amount in calculations as well, to ensure I don't draw
** outside the window and to center the camera.
*/
# define WIDTH (800)
# define HEIGHT (600)

/*
** The base amount of rotation degrees per keypress
*/
# define ROTATION_DEGREES (5)

/*
** The amount of milliseconds for each frame while in the rotation function
*/
# define ROTATION_SPEED_MS (40000)

/*
** Default scale (distance between points in the file)
*/
# define SCALE (30)

/*
** Multiplier for how much z affects the projected point's x and y value
** i.e. the value (1000) says that with a z of 1000, the projected x and y
** value should double
*/
# define VANISHING_POINT (1000)

#endif
