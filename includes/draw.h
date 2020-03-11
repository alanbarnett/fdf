/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:02:39 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/10 20:03:58 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

void	plot_map_line(struct s_fdf *data, int x1, int x2, int y1, int y2);
void	plot_map(struct s_fdf *data);
int		draw_image(struct s_fdf *data);

#endif
