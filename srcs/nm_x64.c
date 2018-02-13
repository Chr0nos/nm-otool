/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:58 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/13 07:23:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		indexes_core(void *userdata, size_t content_size, void *content)
{
	t_nm							*nm;
	const struct segment_command_64	*seg = (void*)(size_t)content;
	const void						*endsector;
	struct section_64				*sec =
		(void*)((size_t)content + sizeof(*seg));

	nm = userdata;
	if (nm_security(nm, seg, content_size) == NM_ERROR)
		return ;
	endsector = (void*)((size_t)sec + (seg->nsects * sizeof(*sec)));
	while ((void*)sec < endsector)
	{
		nm->indexes.sector++;
		if ((!ft_strcmp(seg->segname, SEG_TEXT)) &&
				(!ft_strcmp(sec->sectname, SECT_TEXT)))
			nm->indexes.text = nm->indexes.sector;
		else if (!ft_strcmp(sec->segname, SEG_DATA))
		{
			if (!ft_strcmp(sec->sectname, SECT_BSS))
				nm->indexes.bss = nm->indexes.sector;
			else if (!ft_strcmp(sec->sectname, SECT_DATA))
				nm->indexes.data = nm->indexes.sector;
		}
		sec++;
	}
}

static void		handle_x64_list(t_list **lst,
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

static void		print_symb_64(struct symtab_command *sym, size_t const ptr,
	t_nm *nm)
{
	const char				*stringtable = (char *)(ptr + sym->stroff);
	const struct nlist_64	*array = (void*)(ptr + sym->symoff);
	size_t					i;
	const char				*name;
	t_list					*lst;

	if (nm_security(nm, stringtable, sizeof(*stringtable) * sym->nsyms))
		return ;
	i = 0;
	lst = NULL;
	while (i < sym->nsyms)
	{
		name = &stringtable[array[i].n_un.n_strx];
		handle_x64_list(&lst, &array[i], name);
		i++;
	}
	ft_lstforeach(lst,
		ft_lstforeach(nm->segments, nm, &indexes_core),
		&nm_display_foreach);
	ft_lstdel(&lst, ft_lstpulverisator);
}

void			handle_x64(t_nm *nm)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	size_t						i;

	header = (void*)(size_t)nm->fileraw;
	i = 0;
	lc = (struct load_command*)((size_t)nm->fileraw + sizeof(*header));
	if (nm_security(nm, lc, header->ncmds * sizeof(*lc)) == NM_ERROR)
		return ;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)(size_t)lc;
			print_symb_64(sym, (size_t)nm->fileraw, nm);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			ft_lstpush_back(&nm->segments, ft_lstnewlink(lc, SEGSIZE64));
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
	ft_lstdel(&nm->segments, NULL);
}
