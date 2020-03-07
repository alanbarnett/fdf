/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:24:12 by alan              #+#    #+#             */
/*   Updated: 2020/03/06 22:55:02 by abarnett         ###   ########.fr       */
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
	int		**map;
	int		map_width;
	int		map_height;
	int		img_bits_per_pixel;
	int		img_size_line;
	int		scale;
	int		rotation_speed;
	int		cam_x;
	int		cam_y;
	int		theta_x;
	int		theta_y;
	int		theta_z;
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
** Gets the height of the map. Used for centering the map on screen.
*/

static int			get_map_height(int **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		++i;
	}
	return (i);
}

/*
** Creates the mlx connection, window, and image I will be using. Gets the data
** about the image as well, so it is ready to use.
**
** Scale is an integer that determines my zoom level at this stage. It will be
** multiplied to the x and y offsets of the double array. It is the distance
** between each node of the wireframe.
*/

static struct s_fdf	*fdf_setup(int **map, int width)
{
	struct s_fdf	*data;
	int				endian;

	data = (struct s_fdf *)ft_memalloc(sizeof(struct s_fdf));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "fdf - abarnett");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->img_bits_per_pixel), &(data->img_size_line), &endian);
	data->map = map;
	data->map_width = width;
	data->map_height = get_map_height(map);
	data->scale = 20;
	data->rotation_speed = 10;
	data->cam_x = WIDTH / 2;
	data->cam_y = HEIGHT / 2;
	data->theta_x = 0;
	data->theta_y = 0;
	data->theta_z = 0;
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

#define PI (3.14159265358979f)

void		fdf_put_pixel(struct s_fdf *data, int x, int y, int z)
{
	char	*pixel;

	double	new_x;
	double	new_y;

	double	theta_x;
	double	theta_y;
	double	theta_z;

	// Converting standard angles to radians
	theta_x = (data->theta_x * PI) / 180;
	theta_y = (data->theta_y * PI) / 180;
	theta_z = (data->theta_z * PI) / 180;

	new_x = x * cos(theta_y);
	new_x += z * sin(theta_y);
	new_x -= (x * sin(theta_z) + y * sin(theta_z));

	new_y = y * cos(theta_x);
	new_y += z * sin(theta_x);
	new_y -= (y * sin(theta_z) - x * sin(theta_z));

	new_x += data->cam_x;
	new_y += data->cam_y;

	pixel = &(data->img_data[ (data->img_size_line * (int)new_y) + ((data->img_bits_per_pixel / 8) * (int)new_x) ]);
	pixel[3] = 0;
	pixel[2] = ft_min(z * 2, 255);
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

/*
** Shift coordinates by half the width and height of the map, to center it in
** the coordinate plane. Then project it by scale to make it larger.
*/

void		draw_map_line(struct s_fdf *data, int x1, int x2, int y1, int y2)
{
	struct s_point	start;
	struct s_point	end;

	start.z = data->map[y1][x1] * data->scale;
	end.z = data->map[y2][x2] * data->scale;
	x1 -= (data->map_width / 2);
	x2 -= (data->map_width / 2);
	y1 -= (data->map_height / 2);
	y2 -= (data->map_height / 2);
	start.x = x1 * data->scale;
	start.y = y1 * data->scale;
	end.x = x2 * data->scale;
	end.y = y2 * data->scale;
	fdf_draw_line(data, start, end);
}

void		draw_map(struct s_fdf *data)
{
	for (int i = 0; data->map[i]; ++i)
	{
		for (int j = 0; j < data->map_width; ++j)
		{
			// draw line forward
			if (j + 1 < data->map_width)
			{
				draw_map_line(data, j, j + 1, i, i);
			}
			// draw line down
			if (data->map[i + 1])
			{
				draw_map_line(data, j, j, i, i + 1);
			}
		}
	}
}

int			draw_image(struct s_fdf *data)
{
	ft_bzero(data->img_data, (WIDTH * HEIGHT * (data->img_bits_per_pixel / 8)));
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

void		rotate_y_neg(struct s_fdf *data)
{
	data->theta_y = (data->theta_y - data->rotation_speed) % 360;
}

void		rotate_y_pos(struct s_fdf *data)
{
	data->theta_y = (data->theta_y + data->rotation_speed) % 360;
}

void		rotate_x_neg(struct s_fdf *data)
{
	data->theta_x = (data->theta_x - data->rotation_speed) % 360;
}

void		rotate_x_pos(struct s_fdf *data)
{
	data->theta_x = (data->theta_x + data->rotation_speed) % 360;
}

void		rotate_z_neg(struct s_fdf *data)
{
	data->theta_z = (data->theta_z - data->rotation_speed) % 360;
}

void		rotate_z_pos(struct s_fdf *data)
{
	data->theta_z = (data->theta_z + data->rotation_speed) % 360;
}

int			keycode_func(int keycode, struct s_fdf *data)
{
	static void	(*key_funcs[128])() = {
		[43] = rotate_z_neg,
		[47] = rotate_z_pos,
		[123] = rotate_y_neg,
		[124] = rotate_y_pos,
		[125] = rotate_x_neg,
		[126] = rotate_x_pos,
	};
	ft_printf("keycode: %d\n", keycode);
	if (keycode < 128 && key_funcs[keycode])
		key_funcs[keycode](data);
	draw_image(data);
	return (0);
}

void		fdf(int **map, int width)
{
	struct s_fdf	*data;

	data = fdf_setup(map, width);
	print_map(map, width);
	data->theta_x = 50;
	data->theta_z = 50;
	draw_image(data);
	mlx_key_hook(data->win_ptr, keycode_func, data);
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
