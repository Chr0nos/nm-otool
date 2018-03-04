/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 23:08:07 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 18:10:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "otool.h"
#include "macho.h"
#include "fat.h"
#include "filetype.h"
#include <sys/mman.h>

/*
** if this function is called, then the current file is a know one,
** it's also apparently a valid one (for now...)
*/

static size_t	otool_run_valid(const char *filepath,
	char *fileraw,
	const size_t filesize,
	const size_t flags)
{
	t_otool			otool;

	otool = (t_otool){
		.flags = flags | FLAG_OTOOL | FLAG_SNAME,
		.filepath = filepath,
		.filesize = filesize,
		.fileraw = (unsigned char *)(size_t)fileraw,
		.segments = NULL,
		.rootraw = fileraw,
		.rfs = filesize,
		.subfilename = NULL
	};
	return (otool_stack(&otool));
}

t_otool			*otool_detect(t_otool *otool)
{
	otool->flags |= filetype((void*)otool->fileraw, otool->filesize);
	if (otool->flags & (FLAG_UNKNKOW | FLAG_ERROR))
	{
		ft_dprintf(STDERR_FILENO, "%s",
			"error: unknow subfile type provided\n");
		otool->flags |= FLAG_ERROR;
	}
	return (otool);
}

size_t			otool_stack(t_otool *otool)
{
	if (otool->flags & FLAG_LIB)
		ft_printf("%s%s\n", "Archive : ", otool->filepath);
	else if (otool->flags & FLAG_LIBNAME)
	{
		if (otool->subfilename)
			ft_printf("%s(%s):\n", otool->filepath, otool->subfilename);
	}
	else if (otool->flags & FLAG_SNAME)
		ft_printf("%s:\n", otool->filepath);
	if (otool->flags & FLAG_ERROR)
		return (otool->flags);
	else if (otool->flags & FLAG_MACHO)
		macho((t_common*)otool, &otool_macho_symtab);
	else if (otool->flags & FLAG_FAT)
		fat((t_common*)otool, &otool_fat);
	else if (otool->flags & FLAG_LIB)
		handle_lib((t_common*)otool, &otool_lib);
	else
	{
		ft_dprintf(STDERR_FILENO, "%s", "error: unknow file type provided\n");
		otool->flags |= FLAG_UNKNKOW | FLAG_ERROR;
	}
	return (otool->flags);
}

static int		otool_run(const char *filepath, const int max)
{
	char		*fileraw;
	size_t		filesize;
	size_t		flags;

	fileraw = loadfile(filepath, &filesize);
	if (!fileraw)
	{
		ft_dprintf(STDERR_FILENO, "%s%s\n", "error: failed to open: ",
			filepath);
		return (EXIT_FAILURE);
	}
	flags = filetype(fileraw, filesize);
	if (max > 1)
		flags |= FLAG_SNAME | FLAG_SKIPLINE;
	if (flags & (FLAG_UNKNKOW | FLAG_ERROR))
		ft_dprintf(STDERR_FILENO, "%s", "error: unknow file type provided\n");
	else
		flags = otool_run_valid(filepath, fileraw, filesize, flags);
	munmap(fileraw, filesize);
	return ((flags & FLAG_ERROR) ? EXIT_FAILURE : EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	int			p;
	int			retcode;

	if (ac < 2)
	{
		ft_dprintf(STDERR_FILENO, "%s", "error: missing file path\n");
		return (EXIT_FAILURE);
	}
	retcode = EXIT_SUCCESS;
	p = 1;
	while (p < ac)
		retcode += otool_run(av[p++], ac - 1);
	return (retcode);
}
