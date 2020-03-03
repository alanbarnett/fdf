/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:24:12 by alan              #+#    #+#             */
/*   Updated: 2020/03/02 19:30:52 by abarnett         ###   ########.fr       */
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

struct s_point
{
	int	x;
	int	y;
	int	z;
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

int			line_length(struct s_point start, struct s_point end)
{
	int	x;
	int	y;
	int	z;
	int	len;

	x = ft_abs(start.x - end.x);
	y = ft_abs(start.y - end.y);
	z = ft_abs(start.z - end.z);
	len = sqrt(pow(x, 2) + pow(y, 2));
	len = sqrt(pow(len, 2) + pow(z, 2));
	return (len);
}

void		fdf_put_pixel(struct s_fdf *data, int x, int y, int z)
{
	char	*pixel;

	pixel = &(data->img_data[ (data->img_size_line * (int)y) + ((data->img_bits_per_pixel / 8) * (int)x) ]);
	pixel[3] = 0;
	pixel[2] = z * 20;
	pixel[1] = 0x20;
	pixel[0] = 0xa0;
	(void)z;
}

void		fdf_draw_line(struct s_fdf *data, struct s_point start, struct s_point end)
{
	double	x;
	double	y;
	double	z;
	double	d_x;
	double	d_y;
	double	d_z;
	int		steps;

	steps = line_length(start, end);
	d_x = ((double)(end.x - start.x) / steps);
	d_y = ((double)(end.y - start.y) / steps);
	d_z = ((double)(end.z - start.z) / steps);
	x = start.x;
	y = start.y;
	z = start.z;
	while (steps)
	{
		fdf_put_pixel(data, x, y, z);
		x += d_x;
		y += d_y;
		z += d_z;
		--steps;
	}
}

void		fdf()
{
	struct s_fdf	*data;

	data = fdf_setup();
	struct s_point start = {
		200,
		200,
		0
	};
	struct s_point end = {
		400,
		400,
		10
	};
	struct s_point after = {
		600,
		600,
		0
	};
	fdf_draw_line(data, start, end);
	fdf_draw_line(data, end, after);
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
