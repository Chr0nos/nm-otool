/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 15:33:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"
#include "filetype.h"
#include <sys/mman.h>

int		handle_files_types(t_nm *nm)
{
	nm->flags |= filetype(nm->fileraw, nm->filesize);
	if (nm->flags & FLAG_UNKNKOW)
	{
		ft_dprintf(2, "%s%#x\n", "error: unknow file type: ", nm->magic);
		nm->flags |= FLAG_ERROR;
		return (NM_ERROR);
	}
	if (nm->flags & FLAG_MACHO)
	{
		if (nm->flags & FLAG_32BITS)
			handle_x32(nm);
		else if (nm->flags & FLAG_64BITS)
			handle_x64(nm);
	}
	else if (nm->flags & FLAG_FAT)
		handle_fat(nm);
	else if (nm->flags & FLAG_LIB)
		handle_lib(nm);
	return (NM_SUCCESS);
}

static int	nm_run(const char *filepath, char *fileraw,
	const size_t filesize, const size_t flags)
{
	t_nm	nm;

	ft_bzero(&nm, sizeof(nm));
	nm.flags = flags;
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

static int	main_options(int ac, char **av, size_t *flags)
{
	int		p;

	p = 1;
	if (!ft_strcmp(av[p], "--no-sort"))
	{
		ft_printf("disabled sort\n");
		*flags |= FLAG_NOSORT;
		p++;
	}
	if (!ft_strcmp(av[p], "--by-addr"))
	{
		*flags |= FLAG_BYADDR;
		p++;
	}
	if (p < ac - 1)
		*flags |= FLAG_SNAME;
	return (p);
}

int			main(int ac, char **av)
{
	int			p;
	int			error_count;
	size_t		perma_flags;
	size_t		flags;

	if (ac < 2)
		return (handle_file("a.out", FLAG_NONE));
	perma_flags = FLAG_NM;
	p = main_options(ac, av, &perma_flags);
	error_count = 0;
	while (p < ac)
	{
		flags = (p < ac) ? FLAG_SKIPLINE : FLAG_NONE;
		error_count += handle_file(av[p], flags | perma_flags);
		p++;
	}
	return (error_count);
}
