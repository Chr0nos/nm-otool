/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/09 18:43:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

static void	print_symb_64(struct symtab_command *sym, size_t const ptr)
{
	const char				*stringtable = (char *)(ptr + sym->stroff);
	const struct nlist_64	*array = (void*)(ptr + sym->symoff);
	const char				*name;
	size_t					i;

	i = 0;
	while (i < sym->nsyms)
	{
		name = &stringtable[array[i].n_un.n_strx];
		ft_printf("name: %s\n", name);
		i++;
	}
}

static void	handle_x64(char *fileraw)
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
			ft_printf("nb symboles: %d\n", sym->nsyms);
			print_symb_64(sym, (size_t)fileraw);
			break ;
		}
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
}

static void	handle_files(const char *filepath)
{
	char	*fileraw;
	size_t	size;

	if (!(fileraw = ft_readfile(filepath, &size)))
	{
		ft_dprintf(2, "%s%s\n", "error: failed to open: ", filepath);
		return ;
	}
	if (size < 4)
		ft_dprintf(2, "%s%s\n", "error: invalid file: ", filepath);
	else if (*(unsigned int *)(size_t)fileraw == MH_MAGIC_64)
		handle_x64(fileraw);
	else
		ft_dprintf(2, "%s%s\n", "error: unknow file type: ", filepath);
	free(fileraw);
}

int			main(int ac, char **av)
{
	int		p;

	if (ac < 2)
	{
		ft_dprintf(2, "%s", "usage: ./nm [filepath]\n");
		return (EXIT_FAILURE);
	}
	p = 1;
	while (p < ac)
		handle_files(av[p++]);	
	return (EXIT_SUCCESS);
}
