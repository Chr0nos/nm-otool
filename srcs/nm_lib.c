/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:16:28 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/18 13:20:22 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_lib(t_nm *nm)
{
	ft_printf("library for %s\n", nm->filepath);
	nm->flags |= NM_FLAG_SYMTAB;
}
