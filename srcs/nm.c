/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/11 16:25:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"
#include <sys/mman.h>

char		nm_getletter(const t_sym *sym)
{
	const size_t		type = sym->type & N_TYPE;
	char				ret;

	ret = '?';
	if (type == N_UNDF)
		ret = 'U';
	else if (type == N_PBUD)
		ret = 'U';
	else if (type == N_SECT)
		ret = 'U';
	else if (type == N_ABS)
		ret = 'A';
	else if (type == N_INDR)
		ret = 'I';
	else if (sym->type & N_STAB)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

t_list		*nm_display_list(t_list *lst)
{
	t_list		*origin;
	t_sym		*sym;

	origin = lst;
	while (lst)
	{
		sym = lst->content;
		if (sym->value > 0)
			ft_printf("%08x%08x %1c %s\n",
					sym->type & N_EXT,
					sym->value, nm_getletter(sym), sym->name);
		else
			ft_printf("%16s %1c %s\n", "", 'U', sym->name);
		lst = lst->next;
	}
	return (origin);
}

int			handle_sort(t_list *a, t_list *b)
{
	const t_sym		*as = a->content;
	const t_sym		*bs = b->content;

	if (as->value != bs->value)
		return ((as->value < bs->value) ? 1 : -1);
	return (ft_strcmp(as->name, bs->name));
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
	else if (*(unsigned int *)(size_t)fileraw == MH_MAGIC)
		handle_x32(fileraw);
	else
		ft_dprintf(2, "%s%s\n", "error: unknow file type: ", filepath);
	// free(fileraw);
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
