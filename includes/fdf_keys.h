/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keys.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 01:10:30 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/07 01:37:01 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_KEYS_H
# define FDF_KEYS_H

# define KEY_H (4)
# define KEY_J (38)
# define KEY_K (40)
# define KEY_L (37)
# define KEY_LARR (123)
# define KEY_DARR (125)
# define KEY_UARR (126)
# define KEY_RARR (124)
# define KEY_LSHIFT (257)
# define KEY_Q (12)
# define KEY_R (15)
# define KEY_I (34)
# define KEY_O (31)
# define KEY_COMM (43)
# define KEY_PERIOD (47)

struct s_fdf;

void	quit(struct s_fdf *data);
void	rotate_x_neg(struct s_fdf *data);
void	rotate_x_pos(struct s_fdf *data);
void	rotate_y_neg(struct s_fdf *data);
void	rotate_y_pos(struct s_fdf *data);
void	rotate_z_neg(struct s_fdf *data);
void	rotate_z_pos(struct s_fdf *data);
void	move_left(struct s_fdf *data);
void	move_right(struct s_fdf *data);
void	move_up(struct s_fdf *data);
void	move_down(struct s_fdf *data);
void	zoom_in(struct s_fdf *data);
void	zoom_out(struct s_fdf *data);
void	reset_cam(struct s_fdf *data);

#endif
