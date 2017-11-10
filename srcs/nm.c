/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:13:38 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/10 03:45:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"

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
