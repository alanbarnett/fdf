/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_fdf_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:57:01 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/07 07:01:20 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "ft_parse.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

/*
** This file will take a filename, and convert it into an allocated fdf map. It
** will dynamically allocate new lines if it needs to, but the width of the map
** should be the same for each line (and it will fail if it isn't). The map
** will be null terminated when it returns.
*/

static int	**resize_grid(int **grid, int *capacity)
{
	int	new_capacity;
	int	**new_grid;

	new_capacity = *capacity * 1.5;
	new_grid = (int **)ft_memalloc(sizeof(int *) * (new_capacity + 1));
	if (grid && new_grid)
	{
		while (*capacity >= 0)
		{
			new_grid[*capacity] = grid[*capacity];
			--*capacity;
		}
	}
	*capacity = new_capacity;
	return (new_grid);
}

static int	delete_grid(int **grid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_memdel((void **)&(grid[i]));
		++i;
	}
	ft_memdel((void **)&grid);
	return (0);
}

int			**file_to_fdf_map(const char *filename, int *size)
{
	int		**grid;
	int		*arr;
	int		fd;
	char	*line;
	int		nums;
	int		capacity;
	int		i;

	nums = -1;
	capacity = 128;
	i = 0;
	grid = (int **)ft_memalloc(sizeof(int *) * (capacity + 1));
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		// make line into array, setting count to it's size
		arr = ft_intsplit(line, size);
		// resize if grid is at max size
		if (i >= capacity)
			grid = resize_grid(grid, &capacity);
		// add in new array to grid
		grid[i] = arr;
		++i;
		// set nums if unset still. this will be the valid line length
		if (nums == -1)
			nums = *size;
		// quit and delete grid if the count is not what it should be
		// do this after adding the new array into the grid, so it gets deleted
		// i is the amount of actually added things, delete that size
		else if (nums != *size)
		{
			delete_grid(grid, i);
			grid = 0;
			break ;
		}
	}
	close(fd);
	return (grid);
}
