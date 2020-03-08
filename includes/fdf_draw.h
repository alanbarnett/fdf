/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 05:41:39 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/07 06:55:02 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DRAW_H
# define FDF_DRAW_H

struct s_point
{
	int	x;
	int	y;
	int	z;
};

void	fdf_draw_line(struct s_fdf *data, struct s_point start, struct s_point end);
void	draw_map_line(struct s_fdf *data, int x1, int x2, int y1, int y2);
void	draw_map(struct s_fdf *data);
int		draw_image(struct s_fdf *data);

#endif
