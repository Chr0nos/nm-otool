/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 03:32:37 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 03:32:59 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			nm_wrapper(size_t ptr, t_list *segments, t_common *com)
{
	(void)segments;
	if (com->flags & FLAG_64BITS)
		print_symb_64((void*)ptr, (size_t)com->fileraw, com);
	else if (com->flags & FLAG_32BITS)
		print_symb_32((void*)ptr, (size_t)com->fileraw, com);
}
