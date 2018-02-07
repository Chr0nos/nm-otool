/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:58 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/07 18:26:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_nm	*mkindexes(t_nm *nm)
{
	struct segment_command_64	*seg;
	t_list						*lst;
	unsigned int				index;

	lst = nm->segments;
	index = 0;
	while (lst)
	{
		seg = lst->content;
		if (!ft_strcmp(seg->segname, SEG_TEXT))
			nm->indexes.text = index;
		else if (!ft_strcmp(seg->segname, SEG_DATA))
			nm->indexes.data = index;
		// else if (!ft_strcmp(seg->sectname, SECT_BSS))
			// nm->indexes.bss = index;
		index++;
		lst = lst->next;
	}
	return (nm);
}

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

static void	print_symb_64(struct symtab_command *sym, size_t const ptr,
	t_nm *nm)
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
		i++;
	}
	nm_display_list(lst, mkindexes(nm));
	ft_lstdel(&lst, ft_lstpulverisator);
}

void		handle_x64(t_nm *nm)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	size_t						i;

	header = (void*)(size_t)nm->fileraw;
	i = 0;
	lc = (struct load_command*)((size_t)nm->fileraw + sizeof(*header));
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)(size_t)lc;
			print_symb_64(sym, (size_t)nm->fileraw, nm);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			ft_lstpush_back(&nm->segments, ft_lstnewlink(lc, 0));
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
	ft_lstdel(&nm->segments, NULL);
}
