/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 02:16:50 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/04 18:44:16 by snicolet         ###   ########.fr       */
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

static void	nm_display_foreach(void *content, void *userdata)
{
	const t_nm		*nm = userdata;
	const t_sym		*sym = content;

	if (sym->type & N_DESC_DISCARDED)
		;
	else if (sym->value > 0)
	{
		ft_printf("%0*lx %c %s\n",
			nm->display_size,
			sym->value, nm_getletter(sym, nm->segments), sym->name);
	}
	else
		ft_printf("%*s %c %s\n", nm->display_size, "", 'U', sym->name);
}

t_list		*nm_display_list(t_list *lst, t_nm *nm)
{
	ft_lstforeach(lst, nm, &nm_display_foreach);
	return (lst);
}
