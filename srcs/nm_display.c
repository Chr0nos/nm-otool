/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 02:16:50 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/19 02:13:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char		nm_getletter(const t_sym *sym)
{
	const size_t		type = sym->type & N_TYPE;
	char				ret;

	ret = '?';
	if (type == N_UNDF)
		ret = 'U';
	else if (type == N_PBUD)
		ret = 'U';
	else if (type == N_SECT)
		ret = 'U';
	else if (type == N_ABS)
		ret = 'A';
	else if (type == N_INDR)
		ret = 'I';
	else if (sym->type & N_STAB)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

void		nm_display_sym(const t_sym *sym)
{
	if (sym->value > 0)
		ft_printf("%08x%08x %1c %s\n",
				0,
				sym->value, nm_getletter(sym), sym->name);
	else
		ft_printf("%16s %1c %s\n", "", 'U', sym->name);
}

t_list		*nm_display_list(t_list *lst)
{
	t_list		*origin;

	origin = lst;
	while (lst)
	{
		nm_display_sym(lst->content);
		lst = lst->next;
	}
	return (origin);
}
