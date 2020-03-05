/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:24:12 by alan              #+#    #+#             */
/*   Updated: 2020/03/05 03:26:31 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	int		scale;
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
**
** Scale is an integer that determines my zoom level at this stage. It will be
** multiplied to the x and y offsets of the double array. It is the distance
** between each node of the wireframe.
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
	data->scale = 25;
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
	pixel[2] = z;
	pixel[1] = 0x20;
	pixel[0] = 0xa0;
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

void		print_map(int **map, int size)
{
	for (int i = 0; map[i]; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			ft_printf("%d ", map[i][j]);
		}
		ft_printf("\n");
	}
}

void		draw_map_line(struct s_fdf *data, int **map, int x1, int x2, int y1, int y2)
{
	struct s_point	start;
	struct s_point	end;

	start.x = x1 * data->scale;
	start.y = y1 * data->scale;
	start.z = map[y1][x1] * data->scale;
	end.x = x2 * data->scale;
	end.y = y2 * data->scale;
	end.z = map[y2][x2] * data->scale;
	fdf_draw_line(data, start, end);
}

void		draw_map(struct s_fdf *data, int **map, int width)
{
	for (int i = 0; map[i]; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			// draw line forward
			if (j + 1 < width)
			{
				draw_map_line(data, map, j, j + 1, i, i);
			}
			// draw line down
			if (map[i + 1])
			{
				draw_map_line(data, map, j, j, i, i + 1);
			}
		}
	}
}

void		fdf(int **map, int width)
{
	struct s_fdf	*data;

	data = fdf_setup();
	print_map(map, width);
	draw_map(data, map, width);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
}

int			main(int argc, char **argv)
{
	int	**map;
	int	size;

	map = 0;
	size = 0;
	if (argc == 2)
	{
		ft_printf("%s!\n", argv[1]);
		map = get_grid(argv[1], &size);
		if (!map)
			ft_printf("bad map!\n");
		else
			fdf(map, size);
	}
	else
	{
		show_usage();
	}
	return (0);
}
