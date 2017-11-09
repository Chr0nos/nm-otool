/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/09 17:59:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

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
