/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:21:15 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/05 17:57:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lib.h"
#include "flags.h"
#include "security.h"
#include <ar.h>

static int	load_ar(struct ar_hdr *ar, t_ar *load)
{
	load->ar = ar;
	return (ft_sscanf(ar->ar_name, "%s%u\\s%lu\\s%u\\s%u\\s%x\\s%lu\\s%$",
			AR_EFMT1, &load->len, &load->date, &load->uid, &load->gid,
			&load->mode, &load->size) == 8);
}

static int	lib_cmp(t_ar *a, t_ar *b)
{
	if (a->offset < b->offset)
		return (-1);
	if (a->offset > b->offset)
		return (1);
	return (0);
}

static int	lib_rl_init(t_ar ***tab, t_ar **payload, size_t *flags,
	const size_t size)
{
	void		*ptr;

	if (!(ptr = malloc((sizeof(t_ar) + sizeof(t_ar*)) * size)))
	{
		*flags |= FLAG_ERROR;
		return (FLAG_ERROR);
	}
	*payload = ptr;
	*tab = (t_ar**)((size_t)ptr + (sizeof(t_ar) * size));
	return (FLAG_OK);
}

static void	lib_rl(struct ranlib *rl, const size_t size,
	t_common *com, void (*callback)(t_common *, size_t, const size_t, t_ar **))
{
	size_t				index;
	struct ar_hdr		*ar;
	t_ar				*payload;
	t_ar				**tab;

	if (lib_rl_init(&tab, &payload, &com->flags, size))
		return ;
	index = 0;
	while (index < size)
	{
		ar = (void*)&com->rootraw[rl[index].ran_off];
		payload[index].offset = rl[index].ran_off;
		payload[index].filename = (char*)&ar[1];
		load_ar(ar, &payload[index]);
		tab[index] = &payload[index];
		index++;
	}
	ft_quicksort((void**)tab, 0, size - 1, FT_CASTCMP(&lib_cmp));
	callback(com, 0, size, tab);
	free(payload);
}

/*
** struct ar_hdr                    |
** char		        symdef[?]       |- at_read.len
** int	            size in bytes
** struct ranlib    rl
*/

void		handle_lib(t_common *com,
	void (*callback)(t_common *, size_t, const size_t, t_ar **))
{
	struct ranlib	*rl;
	struct ar_hdr	*ar;
	char			*symdef;
	int				*size;
	t_ar			ar_read;

	ar = (void*)((size_t)com->fileraw + SARMAG);
	symdef = (char*)((size_t)&ar[1]);
	if ((security(com, symdef, 8)) || (!load_ar(ar, &ar_read)))
		return ;
	size = (void*)(&symdef[ar_read.len]);
	rl = (void*)&size[1];
	if (security(com, rl, sizeof(*rl)))
		return ;
	if (*size > 0)
		lib_rl(rl, (size_t)*size / sizeof(struct ranlib), com, callback);
	else
	{
		ar = (void*)&symdef[ar_read.size];
		while ((!(com->flags & FLAG_ERROR)) && (load_ar(ar, &ar_read)))
		{
			ft_printf("%s(%s):\n%s\n", com->filepath,
				(void*)((size_t)ar + sizeof(*ar)),
				"Contents of (__TEXT,__text) section");
			ar = (void*)((size_t)ar + sizeof(*ar) + ar_read.size);
			security(com, ar, sizeof(*ar));
		}
	}
}
