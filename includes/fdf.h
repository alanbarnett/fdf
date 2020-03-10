/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:07:28 by abarnett          #+#    #+#             */
/*   Updated: 2020/04/29 06:26:45 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** Takes a double array map and generates a wireframe with it
** The two dimensions act as x and y, and the value is used as z.
*/
void	fdf(int **map, int width);

/*
** Takes a filename and converts it into a double array for an fdf map.
*/
int		**file_to_fdf_map(const char *filename, int *size);

#endif
