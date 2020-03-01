/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:24:12 by alan              #+#    #+#             */
/*   Updated: 2020/03/01 07:29:44 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "ft_math.h"
#include "ft_printf.h"
#include "mlx.h"
#include <math.h>
#include <unistd.h>

#define WIDTH 1000
#define HEIGHT 800

struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		img_bits_per_pixel;
	int		img_size_line;
};

static void	show_usage(void)
{
	ft_printfd(STDERR_FILENO, "%s\n%s\n%s\n",
			"usage: fdf filename.fdf",
			"Takes a single filename argument",
			"For an example of an fdf file, see mini42.fdf");
}

/*
** Creates the mlx connection, window, and image I will be using. Gets the data
** about the image as well, so it is ready to use.
*/

static struct s_fdf	*fdf_setup()
{
	struct s_fdf	*data;
	int				endian;

	data = (struct s_fdf *)ft_memalloc(sizeof(struct s_fdf));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "fdf - abarnett");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->img_bits_per_pixel), &(data->img_size_line), &endian);
	return (data);
}

int			line_length(int x1, int x2, int y1, int y2)
{
	int	x;
	int	y;
	int	len;

	x = ft_abs(x1 - x2);
	y = ft_abs(y1 - y2);
	len = sqrt(pow(x, 2) + pow(y, 2));
	return (len);
}

void		fdf_draw_line(struct s_fdf *data, int x1, int y1, int x2, int y2)
{
	double	x;
	double	y;
	double	d_x;
	double	d_y;
	int		steps;
	char	*pixel;

	steps = line_length(x1, x2, y1, y2);
	d_x = ((double)(x2 - x1) / steps);
	d_y = ((double)(y2 - y1) / steps);
	x = x1;
	y = y1;
	while (steps)
	{
		pixel = &(data->img_data[ (data->img_size_line * (int)y) + ((data->img_bits_per_pixel / 8) * (int)x) ]);
		pixel[3] = 0;
		pixel[2] = (char)x;
		pixel[1] = (char)y;
		pixel[0] = (char)(x + y);
		y += d_y;
		x += d_x;
		--steps;
	}
}

void		fdf()
{
	struct s_fdf	*data;

	data = fdf_setup();
	fdf_draw_line(data, 200, 200, 400, 400);
	fdf_draw_line(data, 400, 400, 2, 90);
	fdf_draw_line(data, 2, 90, 300, 150);
	fdf_draw_line(data, 300, 150, 200, 200);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
}

int			main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_printf("%s!\n", argv[1]);
	}
	else
	{
		show_usage();
	}
	fdf();
	return (0);
}
