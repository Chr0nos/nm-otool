/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 02:16:50 by snicolet          #+#    #+#             */
/*   Updated: 2017/12/10 02:01:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char	get_address_segment(const unsigned int nsect, t_list *segments)
{
	struct segment_command_64	*seg;
	uint8_t						index;

	index = 0;
	while (segments)
	{
		seg = segments->content;
		if (index == nsect)
		{
			if (!ft_strcmp(seg->segname, SEG_TEXT))
				return (SYM_TEXT);
			else if (!ft_strcmp(seg->segname, SEG_DATA))
				return (SYM_DATA);
			else if (!ft_strcmp(seg->segname, SECT_BSS))
				return (SYM_BSS);
			return ('S');
		}
		index++;
		segments = segments->next;
	}
	return ('S');
}

char		nm_getletter(const t_sym *sym, t_list *segments)
{
	const size_t		type = sym->type & N_TYPE;
	char				ret;

	ret = '?';
	if (type == N_UNDF)
		ret = (sym->value == 0) ? 'U' : 'C';
	else if (type == N_PBUD)
		ret = 'U';
	else if (type == N_SECT)
		ret = get_address_segment(sym->nsect, segments);
	else if (type == N_ABS)
		ret = 'A';
	else if (type == N_INDR)
		ret = 'I';
	else if (sym->type & N_STAB)
		ret = 'Z';
	if ((!(sym->type & N_EXT) && (ret != '?')))
		ret += 32;
	return (ret);
}

void		nm_display_sym(const t_sym *sym, t_list *segments)
{
	if (sym->value > 0)
		ft_printf("%016lx %c %s\n",
			sym->value, nm_getletter(sym, segments), sym->name);
	else
		ft_printf("%16s %c %s\n", "", 'U', sym->name);
}

t_list		*nm_display_list(t_list *lst, t_list *segments)
{
	t_list		*origin;

	origin = lst;
	while (lst)
	{
		nm_display_sym(lst->content, segments);
		lst = lst->next;
	}
	return (origin);
}
