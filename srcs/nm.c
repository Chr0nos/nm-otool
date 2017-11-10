/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/10 14:24:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"

t_list		*nm_display_list(t_list *lst)
{
	t_list		*origin;
	t_sym		*sym;

	origin = lst;
	while (lst)
	{
		sym = lst->content;
		if (sym->value > 0)
			ft_printf("%08x%08x %1s %s\n",
					sym->type & N_EXT,
					sym->value, "X", sym->name);
		else
			ft_printf("%16s %1s %s\n", "", "U", sym->name);
		lst = lst->next;
	}
	return (origin);
}

int			handle_sort(t_list *a, t_list *b)
{
	return (ft_strcmp(
		((t_sym*)(a->content))->name,
		((t_sym*)(b->content))->name));
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
	free(fileraw);
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
