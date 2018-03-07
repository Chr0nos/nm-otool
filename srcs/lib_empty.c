/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_empty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:59:09 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/07 14:59:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lib.h"
#include <ar.h>
#include "flags.h"

void			lib_empty(t_common *com, struct ar_hdr *ar)
{
	t_ar			ar_read;
	char			*filename;
	unsigned char	*fileraw;

	while ((!(com->flags & FLAG_ERROR)) &&
		((void*)ar < (void*)&com->rootraw[com->rfs]) &&
		(load_ar(ar, &ar_read)))
	{
		filename = (void*)((size_t)ar + sizeof(*ar));
		fileraw = (void*)&filename[ft_strlen(filename) + 8];
		ft_printf("%s(%s):\n%s\n", com->filepath, filename,
			"Contents of (__TEXT,__text) section");
		ar = (void*)((size_t)&ar[1] + ar_read.size);
	}
}
