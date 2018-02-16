/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 02:16:50 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/16 12:43:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char get_sect_letter(const t_nm *nm, const unsigned int nsect)
{
	if (nsect == nm->indexes.text)
		return ('T');
	if (nsect == nm->indexes.data)
		return ('D');
	if (nsect == nm->indexes.bss)
		return ('B');
	return ('S');
}

char		nm_getletter(const t_sym *sym, const t_nm *nm)
{
	const size_t		type = sym->type & N_TYPE;
	char				ret;

	if (sym->type == N_STAB)
		return ('-');
	ret = '?';
	if (type == N_UNDF)
		ret = (sym->value == 0) ? 'U' : 'C';
	else if (type == N_PBUD)
		ret = 'U';
	else if (type == N_SECT)
		ret = get_sect_letter(nm, sym->nsect);
	else if (type == N_ABS)
		ret = 'A';
	else if (type == N_INDR)
		ret = 'I';
	if ((!(sym->type & N_EXT) && (ret != '?')))
		ret += 32;
	return (ret);
}

static int	handle_qsort(t_sym *a, t_sym *b)
{
	int				cmp;

	cmp = ft_strcmp(a->name, b->name);
	if (!cmp)
		return ((int)(a->value - b->value));
	return (cmp);
}

void		nm_display(t_list *lst, t_nm *nm)
{
	t_sym		**tab;
	t_sym		*sym;
	size_t		index;
	char		letter;

	if (!(tab = (t_sym**)ft_lstqsort(lst, FT_CASTCMP(&handle_qsort))))
		return ;
	index = 0;
	while (tab[index])
	{
		sym = tab[index];
		if (sym->type & (N_DESC_DISCARDED | N_STAB))
			return ;
		letter = nm_getletter(sym, nm);
		if (!ft_strchr("uU?", letter))
		{
			ft_printf("%0*lx %c %s\n",
				nm->display_size, sym->value, letter, sym->name);
		}
		else
			ft_printf("%*s %c %s\n", nm->display_size, "", 'U', sym->name);
		index++;
	}
	free(tab);
}

void		nm_display_foreach(void *userdata, size_t size, void *content)
{
	const t_nm		*nm = userdata;
	const t_sym		*sym = content;
	char			letter;

	if (sym->type & (N_DESC_DISCARDED | N_STAB))
		return ;
	letter = nm_getletter(sym, nm);
	if (!ft_strchr("uU?", letter))
	{
		ft_printf("%0*lx %c %s\n",
			nm->display_size, sym->value, letter, sym->name, size);
	}
	else
		ft_printf("%*s %c %s\n", nm->display_size, "", 'U', sym->name);
}
