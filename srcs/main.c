/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:24:12 by alan              #+#    #+#             */
/*   Updated: 2020/03/07 07:02:15 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include <unistd.h> //stderr_fileno

static void	show_usage(void)
{
	ft_printfd(STDERR_FILENO, "%s\n%s\n%s\n",
			"usage: fdf filename.fdf",
			"Takes a single filename argument",
			"For an example of an fdf file, see mini42.fdf");
}

int			main(int argc, char **argv)
{
	int	**map;
	int	size;

	map = 0;
	size = 0;
	if (argc == 2)
	{
		map = file_to_fdf_map(argv[1], &size);
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
