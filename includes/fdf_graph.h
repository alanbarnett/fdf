/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graph.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 06:22:41 by alan              #+#    #+#             */
/*   Updated: 2020/04/29 06:26:34 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_GRAPH_H
# define FDF_GRAPH_H

/*
** Takes a function for generating z, and the length of the x and y plane.
** Generates and displays a rotatable and scalable wireframe of the 3D graph.
*/
void	fdf_graph(double (*f_z)(double x, double y), int width, int height);

#endif
