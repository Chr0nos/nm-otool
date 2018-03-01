/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/01 09:33:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"
#include <sys/mman.h>

int			handle_files_types(t_nm *nm)
{
	const t_handlers	ptrs[] = {
		(t_handlers){MH_MAGIC_64, 16, &handle_x64, NM_FLAG_NONE, "64bits"},
		(t_handlers){MH_CIGAM_64, 16, &handle_x64, NM_FLAG_CIGAM, "64bits-cig"},
		(t_handlers){MH_MAGIC, 8, &handle_x32, NM_FLAG_NONE, "32bits"},
		(t_handlers){MH_CIGAM, 8, &handle_x32, NM_FLAG_CIGAM, "32bits-cigam"},
		(t_handlers){FAT_MAGIC_64, 8, &handle_fat, NM_FLAG_NONE, "fat binary"},
		(t_handlers){NM_LIBRARY, 16, &handle_lib, NM_FLAG_NONE, "64 bits lib"},
		(t_handlers){FAT_CIGAM, 8, &handle_fat, NM_FLAG_CIGAM, "fat binary-cig"}
	};
	size_t				p;

	p = 7;
	while (p--)
	{
		if (ptrs[p].magic == nm->magic)
		{
			nm->display_size = ptrs[p].display_size;
			nm->flags |= ptrs[p].flags;
			ptrs[p].run(nm);
			return (NM_SUCCESS);
		}
	}
	nm->flags |= NM_UNKNOW_FILETYPE | NM_FLAG_ERROR;
	ft_dprintf(2, "%s%#x\n", "error: unknow file type: ", nm->magic);
	return (NM_ERROR);
}

static void	handle_real(t_nm *nm, const char *filepath,
	const unsigned int magic)
{
	if (nm->total_files > 1)
		nm->flags |= NM_FLAG_SHOWNAME;
	nm->fileraw = nm->rootraw;
	nm->filesize = nm->rfs;
	nm->filepath = filepath;
	nm->magic = magic;
	handle_files_types(nm);
}

static int	handle_files(const char *filepath, const int files_count,
	const int index)
{
	t_nm		nm;

	ft_bzero(&nm, sizeof(nm));
	if (!(nm.rootraw = loadfile(filepath, &nm.rfs)))
	{
		ft_dprintf(2, "%s%s\n", "error: failed to open: ", filepath);
		return (NM_ERROR);
	}
	if (nm.rfs < 4)
		ft_dprintf(2, "%s%s\n", "error: invalid file: ", filepath);
	else
	{
		nm.total_files = (unsigned int)files_count;
		nm.current_index = (unsigned int)index;
		handle_real(&nm, filepath, *(unsigned int *)(size_t)nm.rootraw);
	}
	munmap(nm.rootraw, nm.rfs);
	if ((!(nm.flags & NM_FLAG_SYMTAB)) && (!(nm.flags & NM_FLAG_ERROR)))
	{
		ft_dprintf(STDERR_FILENO, "%s", "error: no symbols table found.\n");
		return (NM_ERROR);
	}
	return ((nm.flags & NM_FLAG_ERROR) != NM_FLAG_NONE);
}

int			nm_security(t_nm *nm, const void *ptr, const size_t size)
{
	const void		*lastptr;
	const void		*endptr;

	if ((!nm) || (!nm->fileraw))
		return (NM_ERROR);
	lastptr = &nm->rootraw[nm->rfs];
	//lastptr = (void*)((size_t)nm->fileraw + nm->filesize);
	endptr = (void*)((size_t)ptr + size);
	if ((endptr > lastptr) || (ptr < (void*)nm->fileraw))
	{
		ft_dprintf(STDERR_FILENO, "%s", "error: the file is corrupted.\n");
		nm->flags |= NM_FLAG_ERROR;
		return (NM_ERROR);
	}
	return (NM_SUCCESS);
}

int			main(int ac, char **av)
{
	int		p;
	int		errcode;

	if (ac < 2)
		return (handle_files("a.out", 1, 1));
	p = 1;
	errcode = EXIT_SUCCESS;
	while (p < ac)
	{
		errcode += handle_files(av[p], ac - 1, p);
		p++;
	}
	return (errcode);
}
