/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:58 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/10 03:45:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

static void	print_symb_64(struct symtab_command *sym, size_t const ptr)
{
	const char				*stringtable = (char *)(ptr + sym->stroff);
	const struct nlist_64	*array = (void*)(ptr + sym->symoff);
	size_t					i;
	const char				*name;

	i = 0;
	while (i < sym->nsyms)
	{
		name = &stringtable[array[i].n_un.n_strx];
		if (array[i].n_value > 0)
			ft_printf("%08x%08x %1s %s\n",
					array[i].n_type & N_EXT,
					array[i].n_value, "X", name);
		else
			ft_printf("%16s %1s %s\n", "", "U", name);
		i++;
	}
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
