/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 05:41:39 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/10 20:04:27 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DRAW_H
# define FDF_DRAW_H

struct s_point
{
	double	x;
	double	y;
	double	z;
};

void	fdf_plot_pixel(struct s_fdf *data, struct s_point *point);
void	fdf_plot_line(struct s_fdf *data, struct s_point start, struct s_point end);

#endif
