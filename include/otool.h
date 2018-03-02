/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:04:09 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 18:50:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H
# include "loadfile.h"
# include "libft.h"
# include <string.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>
# define OTOOL_FLAG_OK		0
# define OTOOL_FLAG_32BITS	(1u << 0)
# define OTOOL_FLAG_64BITS	(1u << 1)
# define OTOOL_FLAG_LIB		(1u << 2)
# define OTOOL_FLAG_FAT		(1u << 3)
# define OTOOL_FLAG_CIGAM	(1u << 4)
# define OTOOL_FLAG_UNKNKOW	(1u << 5)
# define OTOOL_FLAG_ERROR	(1u << 6)

size_t		otool_filetype(char *fileraw, const size_t filesize);

#endif
