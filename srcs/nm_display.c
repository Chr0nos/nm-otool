/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 02:16:50 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 06:41:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char	get_sect_letter(const t_nm *nm, const unsigned int nsect)
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
	const int	cmp = ft_strcmp(a->name, b->name);

	return ((cmp == 0) ? (int)(a->value - b->value) : cmp);
}

static void	display_name(const t_nm *nm)
{
	if (nm->flags & FLAG_SNAME)
	{
		if (nm->flags & FLAG_LIB)
			ft_printf("\n%s(%s):\n", nm->filepath, nm->subfilename);
		else
			ft_printf((nm->flags & FLAG_SKIPLINE) ? "\n%s:\n" : "%s:\n",
				nm->filepath);
	}
}

void		nm_display(t_list *lst, t_nm *nm)
{
	unsigned int	display_size = (nm->flags & FLAG_64BITS) ? 16 : 8;
	t_sym			**tab;
	t_sym			*sym;
	size_t			index;
	char			letter;

	display_name(nm);
	if ((nm->flags & FLAG_NOSORT) && (!(tab = (t_sym**)ft_lsttotab(lst))))
		return ;
	else if (!(tab = (t_sym**)ft_lstqsort(lst, FT_CASTCMP(&handle_qsort))))
		return ;
	index = 0;
	while (tab[index])
	{
		sym = tab[index++];
		if (sym->type & (N_DESC_DISCARDED | N_STAB))
			continue ;
		letter = nm_getletter(sym, nm);
		if (!ft_strchr("uU?", letter))
			ft_printf("%0*lx %c %s\n",
				display_size, sym->value, letter, sym->name);
		else
			ft_printf("%*s %c %s\n", display_size, "", 'U', sym->name);
	}
	free(tab);
}
