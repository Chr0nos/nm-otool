/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/09 18:15:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"
#include <sys/mman.h>

int			handle_sort(t_list *a, t_list *b)
{
	const t_sym		*as = a->content;
	const t_sym		*bs = b->content;

	return (ft_strcmp(as->name, bs->name));
}

static int	handle_files_types(t_nm *nm)
{
	const t_handlers	ptrs[] = {
		(t_handlers){MH_MAGIC_64, 16, &handle_x64},
		(t_handlers){MH_CIGAM_64, 16, &handle_x64},
		(t_handlers){MH_MAGIC, 8, &handle_x32},
		(t_handlers){MH_CIGAM, 8, &handle_x32},
		(t_handlers){FAT_MAGIC_64, 8, &handle_fat},
		(t_handlers){FAT_CIGAM, 8, &handle_fat}
	};
	size_t				p;

	p = 6;
	while (p--)
	{
		if (ptrs[p].magic == nm->magic)
		{
			nm->display_size = ptrs[p].display_size;
			ptrs[p].run(nm);
			return (NM_SUCCESS);
		}
	}
	ft_dprintf(2, "%s%#x\n", "error: unknow file type: ", nm->magic);
	return (NM_ERROR);
}

static int	handle_files(const char *filepath)
{
	t_nm		nm;

	ft_bzero(&nm, sizeof(nm));
	if (!(nm.fileraw = ft_readfile(filepath, &nm.filesize)))
	{
		ft_dprintf(2, "%s%s\n", "error: failed to open: ", filepath);
		return (NM_ERROR);
	}
	if (nm.filesize < 4)
		ft_dprintf(2, "%s%s\n", "error: invalid file: ", filepath);
	else
	{
		nm.filepath = filepath;
		nm.magic = *(unsigned int *)(size_t)nm.fileraw;
		handle_files_types(&nm);
	}
	munmap(nm.fileraw, nm.filesize);
	return (NM_SUCCESS);
}

int			nm_security(const t_nm *nm, const void *ptr, const size_t size)
{
	const void		*lastptr;
	const void		*endptr;

	if ((!nm) || (!nm->fileraw))
		return (NM_ERROR);
	lastptr = (void*)((size_t)nm->fileraw + (size_t)nm->filesize);
	endptr = (void*)((size_t)ptr + size);
	if (endptr > lastptr)
	{
		ft_dprintf(STDERR_FILENO, "%s", "the file is corrupted.\n");
		return (NM_ERROR);
	}
	return (NM_SUCCESS);
}

int			main(int ac, char **av)
{
	int		p;

	if (ac < 2)
	{
		handle_files("a.out");
		return (EXIT_SUCCESS);
	}
	p = 1;
	while (p < ac)
		handle_files(av[p++]);
	return (EXIT_SUCCESS);
}
