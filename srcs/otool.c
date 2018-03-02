/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 23:08:07 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 18:46:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "otool.h"
#include <sys/mman.h>

static void		otool_showmem(const unsigned char *ptr,
	const size_t size, const size_t offset)
{
	const unsigned char		*lastptr = &ptr[size];
	size_t					pos;

	pos = 0;
	while (ptr < lastptr)
	{
		ft_printf("%016x\t\t%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x"
			" %02x %02x %02x %02x %02x %02x\n",
			pos + offset, ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5],
			ptr[6], ptr[7], ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13],
			ptr[14], ptr[15]);
		ptr += 16;
		pos += 16;
	}
}

static int		otool_run(const char *filepath, const int index, const int max)
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
	if (max > 1)
		ft_printf("%s:\n", filepath);
	(void)index;
	flags = otool_filetype(fileraw, filesize);
	ft_printf("filetype: %lb\n", flags, otool_showmem);
	// otool_showmem((unsigned char*)(size_t)fileraw, filesize, 0);
	// ft_printf("%K", otool_kernel, fileraw, filesize, 0);
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
