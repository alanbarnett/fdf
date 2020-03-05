/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 02:00:43 by abarnett          #+#    #+#             */
/*   Updated: 2020/03/05 02:35:49 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "ft_word.h"
#include "ft_mem.h"

/*
** Returns the atoi value, and also seeks the string forward.
*/

static int	ft_parse_num(const char **str)
{
	int			i;
	int			flag;
	const char	*cur;

	i = 0;
	flag = 1;
	cur = *str;
	while (ft_isspace(*cur))
		cur++;
	if (*cur == '-' || *cur == '+')
		flag = (*cur++ == '-' ? -1 : 1);
	while (ft_isdigit(*cur))
		i = (i * 10) + (*cur++ - 48);
	*str = cur;
	return (i * flag);
}

/*
** Splits integers out of a string separated by whitespace
*/

int			*int_split(const char *s, int *size)
{
	int	*ints;
	int	i;

	if (!s)
		return (0);
	*size = ft_wordcount(s);
	ints = (int *)ft_memalloc(sizeof(int) * *size);
	if (!ints)
		return (0);
	i = 0;
	while (i < *size)
	{
		ints[i] = ft_parse_num(&s);
		i++;
	}
	ints[i] = 0;
	return (ints);
}
