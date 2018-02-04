/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/04 18:42:14 by snicolet         ###   ########.fr       */
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

static void	handle_files_types(unsigned int magic, char *fileraw,
		const char *filepath)
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
	t_nm				nm;

	ft_bzero(&nm, sizeof(nm));
	p = 6;
	while (p--)
	{
		if (ptrs[p].magic == magic)
		{
			nm.magic = magic;
			nm.fileraw = fileraw;
			nm.filepath = filepath;
			nm.display_size = ptrs[p].display_size;
			ptrs[p].run(&nm);
			return ;
		}
	}
	ft_dprintf(2, "%s%#x\n", "error: unknow file type: ", magic);
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
	handle_files_types(*(unsigned int *)(size_t)fileraw, fileraw, filepath);
	munmap(fileraw, size);
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
