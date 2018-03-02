/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_security.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 19:38:20 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 19:45:54 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

size_t		otool_security(const char *fileraw, const size_t rawsize,
	const void *ptr)
{
	if  ((ptr < (const void*)fileraw) || (ptr > (const void*)&fileraw[rawsize]))
	{
		ft_dprintf(STDERR_FILENO, "%s\n", "error: the file is corrupted.");
		return (OTOOL_FLAG_ERROR);
	}
	return (OTOOL_FLAG_OK);
}
