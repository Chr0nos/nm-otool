/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:42:24 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/13 08:20:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

// BUG - FIXME
// ici SEC ne se trouve pas reelement apres seg en memoire car seg a ete re malloc
static void		indexes_core(void *userdata, size_t content_size, void *content)
{
	t_nm							*nm;
	const struct segment_command	*seg = (void*)(size_t)content;
	const void						*endsector;
	struct section					*sec = (void*)content_size;

	nm = userdata;
	if (nm_security(nm, sec, sizeof(struct section) * seg->nsects) == NM_ERROR)
		return ;
	endsector = (void*)((size_t)sec + (seg->nsects * sizeof(*sec)));
	ft_printf("%s -> %s : %u\n", sec->segname, sec->sectname, seg->nsects);
	while ((void*)sec < endsector)
	{
		nm->indexes.sector++;
		ft_printf("%s -> %s\n", sec->segname, sec->sectname);
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

static void	handle_x32_list(t_list **lst,
	const struct nlist *item, const char *name)
{
	t_sym		sym;

	sym.name = (char*)(size_t)name;
	sym.type = item->n_type;
	sym.value = item->n_value;
	sym.nsect = (unsigned int)item->n_sect;
	sym.ndesc = (unsigned int)item->n_desc;
	ft_lstpush_sort(lst, ft_lstnew(&sym, sizeof(sym)), &handle_sort);
}

static void	print_symb_32(struct symtab_command *sym, size_t const ptr,
		t_nm *nm)
{
	const char				*stringtable = (char *)(ptr + sym->stroff);
	const struct nlist		*array = (void*)(ptr + sym->symoff);
	size_t					i;
	const char				*name;
	t_list					*lst;

	i = 0;
	lst = NULL;
	while (i < sym->nsyms)
	{
		name = &stringtable[array[i].n_un.n_strx];
		handle_x32_list(&lst, &array[i],  name);
		i++;
	}
	ft_lstforeach(lst,
		ft_lstforeach(nm->segments, nm, &indexes_core),
		&nm_display_foreach);
	ft_lstdel(&lst, ft_lstpulverisator);
}

static void		handle_x32_segment(t_nm *nm, struct load_command *lc)
{
	struct segment_command		*seg;
	struct segment_command_64	*nseg;
	struct section				*sec;

	if (!(nseg = malloc(sizeof(*nseg))))
		return ;
	seg = (void*)lc;
	sec = (void*)((size_t)seg + sizeof(*seg));
	ft_strcpy(nseg->segname, seg->segname);
	nseg->nsects = seg->nsects;
	ft_lstpush_back(&nm->segments, ft_lstnewlink(nseg, (size_t)sec));
}

void			handle_x32(t_nm *nm)
{
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	size_t						i;

	header = (void*)nm->fileraw;
	i = 0;
	lc = (struct load_command *)((size_t)nm->fileraw + sizeof(*header));
	if (nm_security(nm, lc, header->ncmds * sizeof(*lc)) == NM_ERROR)
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
			handle_x32_segment(nm, lc);
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
	ft_lstdel(&nm->segments, &ft_lstpulverisator);
}
