/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 02:43:52 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 02:46:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macho.h"

static size_t	macho_items(const t_common *com)
{
	size_t			size;

	size = 0;
	if (com->flags & FLAG_64BITS)
		size = ((struct mach_header_64 *)(size_t)com->fileraw)->ncmds;
	if (com->flags & FLAG_32BITS)
		size = ((struct mach_header *)(size_t)com->fileraw)->ncmds;
	if (com->flags & FLAG_CIGAM)
		return (swap64(size));
	return (size);
}

void			macho(t_common *com,
	void (*symcall)(size_t, t_list *, t_common *))
{
	struct load_command		*lc;
	size_t					i;
	const size_t			ncmds = macho_items(com);

	lc = (void*)&com->fileraw[com->flags & FLAG_64BITS ?
		sizeof(struct mach_header_64) : sizeof(struct mach_header)];
	i = 0;
	while ((i++ < ncmds) &&
		(!security(com, lc, sizeof(*lc))))
	{
		if (lc->cmd == LC_SYMTAB)
			symcall((size_t)lc, com->segments, com);
		else if (lc->cmd == LC_SEGMENT_64)
			ft_lstadd(&com->segments, ft_lstnewlink(lc, SEGSIZE64));
		else if (lc->cmd == LC_SEGMENT)
			ft_lstadd(&com->segments, ft_lstnewlink(lc, SEGSIZE32));
		lc = (void*)((size_t)lc + lc->cmdsize);
	}
	ft_lstdel(&com->segments, NULL);
}
