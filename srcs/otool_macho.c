/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 19:02:18 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

size_t		otool_macho(char *fileraw, size_t filesize, const size_t flags)
{
	struct mach_header		*header;
	struct load_command		*lc;

	header = (void*)fileraw;
	lc = (void*)nm->fileraw[sizeof(*header)];
	return (OTOOL_FLAG_OK);
}
