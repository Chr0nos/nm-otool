/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 06:45:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"
#include <sys/mman.h>

int			handle_files_types(t_nm *nm)
{
	const t_handlers	ptrs[] = {
		(t_handlers){0, MH_MAGIC_64, &handle_x64, FLAG_NONE, "64bits"},
		(t_handlers){0, MH_CIGAM_64, &handle_x64, FLAG_CIGAM, "64bits-cig"},
		(t_handlers){0, MH_MAGIC, &handle_x32, FLAG_NONE, "32bits"},
		(t_handlers){0, MH_CIGAM, &handle_x32, FLAG_CIGAM, "32bits-cigam"},
		(t_handlers){0, FAT_MAGIC_64, &handle_fat, FLAG_NONE, "fat binary"},
		(t_handlers){0, NM_LIBRARY, &handle_lib, FLAG_NONE, "64 bits lib"},
		(t_handlers){0, FAT_CIGAM, &handle_fat, FLAG_CIGAM, "fat binary-cig"}
	};
	size_t				p;

	p = 7;
	while (p--)
	{
		if (ptrs[p].magic == nm->magic)
		{
			nm->flags |= ptrs[p].flags;
			ptrs[p].run(nm);
			return (NM_SUCCESS);
		}
	}
	nm->flags |= FLAG_UNKNKOW | FLAG_ERROR;
	ft_dprintf(2, "%s%#x\n", "error: unknow file type: ", nm->magic);
	return (NM_ERROR);
}

static int	nm_run(const char *filepath, char *fileraw,
	const size_t filesize, const size_t flags)
{
	t_nm	nm;

	ft_bzero(&nm, sizeof(nm));
	nm.flags = flags | FLAG_NM;
	nm.rfs = filesize;
	nm.filesize = filesize;
	nm.rootraw = fileraw;
	nm.fileraw = fileraw;
	if (security((t_common*)&nm, fileraw, sizeof(unsigned int) +
			sizeof(struct mach_header)))
		return  (1);
	nm.magic = *(unsigned int *)(size_t)fileraw;
	nm.filepath = filepath;
	handle_files_types(&nm);
	if ((!(nm.flags & FLAG_SYMTAB)) && (!(nm.flags & FLAG_ERROR)))
	{
		ft_dprintf(STDERR_FILENO, "%s", "error: no symbols table found.\n");
		return (1);
	}
	return (!((nm.flags & FLAG_ERROR) == FLAG_NONE));
}

static int	handle_file(const char *filepath, const size_t flags)
{
	char		*fileraw;
	size_t		filesize;
	int			ret;

	fileraw = loadfile(filepath, &filesize);
	if ((!fileraw) || (!filesize))
	{
		ft_dprintf(2, "%s%s\n", "error: failed to open: ", filepath);
		return (NM_ERROR);
	}
	ret = nm_run(filepath, fileraw, filesize, flags);
	munmap(fileraw, filesize);
	return (ret);
}

int			main(int ac, char **av)
{
	int		p;
	int		errcode;
	size_t	flags;

	if (ac < 2)
		return (handle_file("a.out", FLAG_NONE));
	p = 1;
	errcode = EXIT_SUCCESS;
	while (p < ac)
	{
		flags = (ac < p) ? FLAG_SNAME | FLAG_SKIPLINE : FLAG_NONE;
		errcode += handle_file(av[p], flags);
		p++;
	}
	return (errcode);
}
