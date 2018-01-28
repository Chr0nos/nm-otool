/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2018/01/28 11:45:46 by snicolet         ###   ########.fr       */
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

static void	handle_files_types(unsigned int magic, char *fileraw)
{
	const t_handlers	ptrs[] = {
		(t_handlers){MH_MAGIC_64, 0, &handle_x64},
		(t_handlers){MH_CIGAM_64, 0, &handle_x64},
		(t_handlers){MH_MAGIC, 0, &handle_x32},
		(t_handlers){MH_CIGAM, 0, &handle_x32},
		(t_handlers){FAT_MAGIC_64, 0, &handle_fat},
		(t_handlers){FAT_CIGAM, 0, &handle_fat}
	};
	size_t				p;

	p = 6;
	while (p--)
	{
		if (ptrs[p].magic == magic)
		{
			ptrs[p].run(fileraw);
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
	handle_files_types(*(unsigned int *)(size_t)fileraw, fileraw);
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
