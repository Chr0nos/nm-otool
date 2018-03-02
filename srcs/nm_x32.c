/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:42:24 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 23:07:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

static void			indexes_core(void *userdata, size_t content_size,
	void *content)
{
	t_nm							*nm;
	const struct segment_command	*seg = (void*)(size_t)content;
	const void						*endsector;
	struct section					*sec;

	sec = (void*)((size_t)seg + sizeof(*seg));
	nm = userdata;
	if (security((t_common*)nm, sec, content_size * seg->nsects))
		return ;
	endsector = (void*)((size_t)sec + (seg->nsects * sizeof(*sec)));
	while ((void*)sec < endsector)
	{
		nm->indexes.sector++;
		if ((!ft_strcmp(sec->segname, SEG_TEXT)) &&
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

static void			handle_x32_list(t_list **lst,
	const struct nlist *item, const char *name, t_nm *nm)
{
	t_sym		sym;

	if (security((t_common*)nm, name, 0))
		return ;
	sym.name = (char*)(size_t)name;
	sym.type = item->n_type;
	sym.value = item->n_value;
	sym.nsect = (unsigned int)item->n_sect;
	sym.ndesc = (unsigned int)item->n_desc;
	ft_lstpush_front(lst, ft_lstnew(&sym, sizeof(sym)));
}

static void			print_symb_32(struct symtab_command *sym, size_t const ptr,
		t_nm *nm)
{
	const char				*stringtable = (char *)(ptr + sym->stroff);
	const struct nlist		*array = (void*)(ptr + sym->symoff);
	size_t					i;
	const char				*name;
	t_list					*lst;

	nm->flags |= FLAG_SYMTAB;
	i = 0;
	lst = NULL;
	while ((i < sym->nsyms) && (!(nm->flags & FLAG_ERROR)))
	{
		name = &stringtable[array[i].n_un.n_strx];
		handle_x32_list(&lst, &array[i], name, nm);
		i++;
	}
	if (!(nm->flags & FLAG_ERROR))
		nm_display(lst, ft_lstforeach(nm->segments, nm, &indexes_core));
	ft_lstdel(&lst, ft_lstpulverisator);
	ft_lstdel(&nm->segments, NULL);
}

void				handle_x32(t_nm *nm)
{
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	size_t						i;

	header = (void*)nm->fileraw;
	i = 0;
	lc = (struct load_command *)((size_t)nm->fileraw + sizeof(*header));
	if (security((t_common*)nm, lc, header->ncmds * sizeof(*lc)))
		return ;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)(size_t)lc;
			print_symb_32(sym, (size_t)nm->fileraw, nm);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT)
			ft_lstpush_back(&nm->segments, ft_lstnewlink(lc, SEGSIZE32));
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
}
