/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_sname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:05:31 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/07 15:06:01 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "libft.h"

void	otool_sname(const t_otool *otool)
{
	if (otool->flags & FLAG_SNAME)
	{
		if (otool->flags & FLAG_LIBNAME)
		{
			if (otool->subfilename)
				ft_printf("%s(%s):\n", otool->filepath, otool->subfilename);
		}
		else if (otool->flags & FLAG_LIB)
			ft_printf("%s%s\n", "Archive : ", otool->filepath);
		else
			ft_printf("%s:\n", otool->filepath);
	}
}
