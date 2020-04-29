/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_fdf_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:57:01 by abarnett          #+#    #+#             */
/*   Updated: 2020/04/16 00:03:04 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "ft_string.h"
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

static void	fill_grid(int fd, int ***grid, int *size)
{
	int		*arr;
	char	*line;
	int		nums;
	int		capacity;
	int		i;

	nums = -1;
	capacity = 128;
	i = 0;
	line = 0;
	*grid = (int **)ft_memalloc(sizeof(int *) * (capacity + 1));
	while (get_next_line(fd, &line))
	{
		// make line into array, setting count to its size
		arr = ft_intsplit(line, size);
		// free line
		ft_strdel(&line);
		// resize if grid is at max size
		if (i >= capacity)
			*grid = resize_grid(*grid, &capacity);
		// add in new array to grid
		(*grid)[i++] = arr;
		// set nums if unset still. this will be the valid line length
		if (nums == -1)
			nums = *size;
		// quit and delete grid if the count is not what it should be
		// do this after adding the new array into the grid, so it gets deleted
		// i is the amount of actually added things, delete that size
		else if (nums != *size)
		{
			delete_grid(*grid, i);
			*grid = 0;
			break ;
		}
	}
	ft_strdel(&line);
}

/*
** Create a grid from an fdf file
**
** Size will be set to the horizontal width of the map. The vertical height
** will be null terminated.
**
** Size is set in this function to the initial capacity of the dynamic grid,
** this is so the capacity can be set in the function to fill the grid and it
** can be allocated to it's initial size here.
*/

int			**file_to_fdf_map(const char *filename, int *size)
{
	int		**grid;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	grid = 0;
	fill_grid(fd, &grid, size);
	close(fd);
	return (grid);
}
