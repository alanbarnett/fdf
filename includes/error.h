/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 23:28:13 by alan              #+#    #+#             */
/*   Updated: 2019/12/09 23:28:51 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
** This enum is for the possible error codes. Leave ERROR_MESSAGE_COUNT as the
** last item, as it represents the size of the error strings array and is used
** for bounds checking when relating the codes to their actual string message.
** Make sure if you add a new code to add the proper string in error.c, in the
** get_error_string function.
*/

enum	e_err_code
{
	E_NOARGS = 1,
	E_NOFILE,
	E_INVALIDFILE,
	ERROR_MESSAGE_COUNT,
};

int	print_error(enum e_err_code error_code);

#endif
