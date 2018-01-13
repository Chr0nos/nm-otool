/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:42:24 by snicolet          #+#    #+#             */
/*   Updated: 2018/01/13 08:37:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

static void	handle_x32_list(t_list **lst,
	const struct nlist *item, const char *name)
{
	t_sym		sym;

	sym.name = (char*)(size_t)name;
	sym.type = item->n_type;
	sym.value = item->n_value;
	sym.nsect = (unsigned int)item->n_sect;
	sym.ndesc = (unsigned int)item->n_desc;
	sym.display_size = 8;
	ft_lstpush_sort(lst, ft_lstnew(&sym, sizeof(sym)), &handle_sort);
}

static void	print_symb_32(struct symtab_command *sym, size_t const ptr,
	t_list *segments)
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
	nm_display_list(lst, segments);
	ft_lstdel(&lst, ft_lstpulverisator);
}

static void		handle_x32_segment(t_list **segments, struct load_command *lc)
{
	struct segment_command		*seg;
	struct segment_command_64	*nseg;

	if (!(nseg = malloc(sizeof(*seg))))
		return ;
	seg = (void*)lc;
	ft_strcpy(nseg->segname, seg->segname);
	nseg->nsects = seg->nsects;
	ft_lstpush_back(segments, ft_lstnewlink(nseg, 0));
}

void			handle_x32(char *fileraw)
{
	t_list						*segments;
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	size_t						i;

	header = (void*)fileraw;
	i = 0;
	lc = (struct load_command *)((size_t)fileraw + sizeof(*header));
	segments = NULL;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)(size_t)lc;
			print_symb_32(sym, (size_t)fileraw, segments);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT)
			handle_x32_segment(&segments, lc);
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
	ft_lstdel(&segments, &ft_lstpulverisator);
}
