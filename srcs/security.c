/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 19:38:20 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 03:08:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "security.h"
#include "otool.h"

size_t		security(t_common *com, const void *ptr, const size_t size)
{
	const unsigned char	*fileraw = com->rootraw;
	const size_t		rawsize = com->rfs;


	if (com->flags & FLAG_ERROR)
		return (FLAG_ERROR);
	ptr = (const void *)((size_t)ptr + size);
	if  ((ptr < (const void*)fileraw) || (ptr > (const void*)&fileraw[rawsize]))
	{
		com->flags |= FLAG_ERROR;
		ft_dprintf(STDERR_FILENO, "%s\n", "error: the file is corrupted.");
		return (FLAG_ERROR);
	}
	return (FLAG_OK);
}
