/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_x32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:42:24 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/10 03:42:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

void	handle_x32(char *fileraw)
{
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	size_t						i;

	ft_printf("%s\n", "valid 32 bits file handled");
	header = (void*)fileraw;
	i = 0;
	lc = (struct load_command *)((size_t)fileraw + sizeof(*header));
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)(size_t)lc;
			break ;
		}
		i++;
	}
}
