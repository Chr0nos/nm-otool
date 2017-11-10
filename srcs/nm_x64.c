/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:58 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/10 21:21:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	handle_x64_list(t_list **lst,
	const struct nlist_64 *item, const char *name)
{
	t_sym		sym;

	sym.name = (char*)(size_t)name;
	sym.type = item->n_type;
	sym.value = item->n_value;
	sym.nsect = (unsigned int)item->n_sect;
	sym.ndesc = (unsigned int)item->n_desc;
	ft_lstpush_sort(lst, ft_lstnew(&sym, sizeof(sym)), &handle_sort);
}

static void	print_symb_64(struct symtab_command *sym, size_t const ptr)
{
	const char				*stringtable = (char *)(ptr + sym->stroff);
	const struct nlist_64	*array = (void*)(ptr + sym->symoff);
	size_t					i;
	const char				*name;
	t_list					*lst;

	i = 0;
	lst = NULL;
	while (i < sym->nsyms)
	{
		name = &stringtable[array[i].n_un.n_strx];
		handle_x64_list(&lst, &array[i],  name);
		ft_printf("%hhu\n", array[i].n_sect);
		i++;
	}
	nm_display_list(lst);
	ft_lstdel(&lst, ft_lstpulverisator);
}

void		handle_x64(char *fileraw)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	size_t						i;

	ft_printf("%s\n", "valid 64 bits file handled");
	header = (void*)(size_t)fileraw;
	i = 0;
	lc = (struct load_command*)((size_t)fileraw + sizeof(*header));
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)(size_t)lc;
			print_symb_64(sym, (size_t)fileraw);
			break ;
		}
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
}
