/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 23:08:07 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 21:30:18 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "otool.h"
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
		.flags = flags,
		.filepath = filepath,
		.filesize = filesize,
		.fileraw = (unsigned char *)(size_t)fileraw,
		.segments = NULL,
		.padding = NULL
	};
	ft_printf("filepath: %s\n", filepath);
	if (flags & (OTOOL_FLAG_64BITS | OTOOL_FLAG_32BITS))
		otool_macho(&otool);
	return (otool.flags);
}

static int		otool_run(const char *filepath, const int index, const int max)
{
	char		*fileraw;
	size_t		filesize;
	size_t		flags;

	(void)index;
	fileraw = loadfile(filepath, &filesize);
	if (!fileraw)
	{
		ft_dprintf(STDERR_FILENO, "%s%s\n", "error: failed to open: ",
			filepath);
		return (EXIT_FAILURE);
	}
	if (max > 1)
		ft_printf("%s:\n", filepath, otool_showmem);
	flags = otool_filetype(fileraw, filesize);
	// ft_printf("filetype: %lb\n", flags, otool_showmem);
	if (flags & (OTOOL_FLAG_UNKNKOW | OTOOL_FLAG_ERROR))
		ft_dprintf(STDERR_FILENO, "%s", "error: unknow file type provided\n");
	else
		otool_run_valid(filepath, fileraw, filesize, flags);
	// otool_showmem((void*)fileraw, filesize, 0, flags);
	munmap(fileraw, filesize);
	return (EXIT_SUCCESS);
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
	{
		retcode += otool_run(av[p], p, ac - 1);
		p++;
	}
	return (retcode);
}
